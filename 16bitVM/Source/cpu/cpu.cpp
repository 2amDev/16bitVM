#include "cpu.hpp"

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
    }

}