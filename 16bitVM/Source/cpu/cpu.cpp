#include "cpu.hpp"

#ifdef DEBUG16BITVM
#include <iostream>
#include <string>
#include <map>

namespace
{
    std::map<std::string, tasm::op> opcode_name_to_enum =
    {
        {"NOP",  tasm::op::NOP},
        {"ADD",  tasm::op::ADD},
        {"SUB",  tasm::op::SUB},
        {"MULT", tasm::op::MULT},
        {"CMP",  tasm::op::CMP},
        {"MOV",  tasm::op::MOV},
        {"JMP",  tasm::op::JMP},
        {"JNZ",  tasm::op::JNZ},
        {"JZ",   tasm::op::JZ},
        {"PUSH", tasm::op::PUSH},
        {"POP",  tasm::op::POP},
        {"CALL", tasm::op::CALL},
        {"RET",  tasm::op::RET}
    };
}
#endif 

void cpu::execute_all(int16_t start_ip)
{
    r[IP] = start_ip;
    while (!r[EF])
    {
        single_step(txt[r[IP]]);
    }

    debug_info();
} 

void cpu::single_step(tasm::ins& ins)
{

    int bp = 0;

    auto move_value_of_into_reg = [&](_r r_type, int8_t x) {
        switch (ins.cf[x])
        {
        case tasm::D:
            r[r_type] = ins.v[x];
            return;
        case tasm::R:
            r[r_type] = r[ins.v[x]];
            return;
        case tasm::P:
            r[r_type] = heap[ins.v[x]];
            return;
        case tasm::RFP:
            r[r_type] = stack[r[FP] + ins.v[x]];
            return;
        case tasm::RSP:
            r[r_type] = stack[r[SP] + ins.v[x]];
            return;
        }
    };

    switch (ins.opcode)
    {
    case tasm::op::NOP:
        break;
    case tasm::op::ADD:
        move_value_of_into_reg(A, 0);
        move_value_of_into_reg(B, 1);
        r[ROP] = r[A] + r[B];
        break;
    case tasm::op::SUB:
        move_value_of_into_reg(A, 0);
        move_value_of_into_reg(B, 1);
        r[ROP] = r[A] - r[B];
        break;
    case tasm::op::MULT:
        move_value_of_into_reg(A, 0);
        move_value_of_into_reg(B, 1);
        r[ROP] = r[A] * r[B];
        break;
    case tasm::op::CMP:
        move_value_of_into_reg(A, 0);
        move_value_of_into_reg(B, 1);
        r[ROP] = r[A] == r[B];
        break;
    case tasm::op::MOV:
        move_value_of_into_reg(B, 1);
        switch (ins.cf[0])
        {
        case tasm::R:
            r[ins.v[0]] = r[B];
            break;
        case tasm::P:
            heap[ins.v[0]] = r[B];
            break;
        case tasm::RFP:
            stack[r[FP] + ins.v[0]] = r[B];
            break;
        case tasm::RSP:
            stack[r[SP] + ins.v[0]] = r[B];
            break;
        }
        break;
    case tasm::op::JMP:
        /* choose if relative or absolute jmp */
        r[IP] = ins.cf[0] ? ins.v[0] : r[IP] + ins.v[0];
        return;
    case tasm::op::JNZ:
        if (r[ROP])
        {
            r[IP] = ins.cf[0] ? ins.v[0] : r[IP] + ins.v[0];
            return;
        }
        break;
    case tasm::op::JZ:
        if (!r[ROP])
        {
            r[IP] = ins.cf[0] ? ins.v[0] : r[IP] + ins.v[0];
            return;
        }
        break;
    case tasm::op::PUSH:
        move_value_of_into_reg(A, 0);
        stack[r[SP]] = r[A];
        r[SP]++;
        break;
    case tasm::op::POP:
        r[SP]--;
        break;
    case tasm::op::CALL:
        stack[r[SP]] = r[IP];
        stack[r[SP] + 1] = r[FP];
        r[SP] += 2;
        r[FP] = r[SP];
        r[IP] = ins.cf[0] ? ins.v[0] : r[IP] + ins.v[0];
        return;
    case tasm::op::RET:
        r[SP] = r[FP];
        r[IP] = stack[r[FP] - 2];
        r[FP] = stack[r[FP] - 1];
        retur
    case tasm::op::INT3:
        r[EF] = 1;
        break;
    }
    r[IP]++;
}

void cpu::debug_info()
{
#ifdef DEBUG16BITVM
    int64_t stack_printf_start = r[SP] <= 10 ? 0 : r[SP] - 10;
    printf("\nstack view:");
    for (int64_t i = stack_printf_start; i < r[SP] + 10; i++)
    {
        std::string additional_buffer = "\nstack[%i] ";
        for (int j = std::to_string(i).length(); j <= 2; j++)
            additional_buffer += " ";
        additional_buffer += "= %i";
        if (i == r[SP])
            additional_buffer += " <------ SP";
        if (i == r[FP])
            additional_buffer += " <------ FP";
        printf(additional_buffer.c_str(), i, stack[i]);
    }
#endif                  
}