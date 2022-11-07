#pragma once

#include <stdint.h>

namespace tasm
{

    enum op
    {
        NOP,
        ADD,
        SUB,
        MULT,
        CMP,
        MOV,
        JMP,
        JNZ,
        JZ,
        PUSH,
        POP,
        CALL,
        RET,
        INT3
    };

    /* Used in an instruction to say if the corresponding int16_t is to be used as itself, correspond to a register, is a pointer to an object type,
    is relative to the stack pointer, or is relative to the frame pointer */
    enum cntr
    {
        D,      
        R,
        P,
        RFP,
        RSP
    };

    struct ins
    {
        op      opcode = NOP;
        cntr    cf[2]  = { D };
        int16_t v[2]   = { 0 };
    };
}