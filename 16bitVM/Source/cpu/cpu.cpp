#include "cpu.hpp"

#ifdef DEBUG16BITVM
#include <iostream>
#include <string>
#endif 

void cpu::execute(tasm::ins& ins)
{
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
        r[ROP] = r[A] + r[B];
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
        r[IP] = ins.cf[0] ? ins.v[0] : stack[IP] + ins.v[0];
        return;
    case tasm::op::JNZ:
        if (r[ROP])
        {
            r[IP] = ins.cf[0] ? ins.v[0] : stack[IP] + ins.v[0];
            return;
        }
        break;
    case tasm::op::JZ:
        if (!r[ROP])
        {
            r[IP] = ins.cf[0] ? ins.v[0] : stack[IP] + ins.v[0];
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
        stack[r[SP]] = r[FP];
        r[SP]++;
        r[FP] = r[SP];
        r[IP] = ins.cf[0] ? ins.v[0] : stack[IP] + ins.v[0];
        break;
    case tasm::op::RET:
        r[SP] = r[FP];
        r[FP] = r[r[FP] - 1];
        break;
    }
    r[IP]++;
}


void cpu::debug_info()
{
#ifdef DEBUG16BITVM
    r[SP] = 50;
    int64_t stack_printf_start = r[SP] <= 10 ? 0 : r[SP] - 10;
    printf("\nSTACK:");
    for (int64_t i = stack_printf_start; i < r[SP] + 10; i++)
    {
        i == r[SP] ? printf("\nstack[%i] = %i <--- STACK POINTER", i, stack[i]) : printf("\nstack[%i] = %i", i, stack[i]);
    }
#endif                  
}