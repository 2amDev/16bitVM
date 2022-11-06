#pragma once

#include <stdint.h>

#include "../tinyasm/tinyasm.hpp"

#define MAX_HEAP_SIZE  1000
#define MAX_STACK_SIZE 1000

class cpu
{
public:

    /* no reason for the heap or stack to be in a cpu class, but it might as well be here temporarily */
    int16_t heap[MAX_HEAP_SIZE];
    int16_t stack[MAX_STACK_SIZE];

    enum _r { IP, SP, FP, ROP, A, B, C, D };
    int16_t r[8];

    void execute(tasm::ins& ins);

};