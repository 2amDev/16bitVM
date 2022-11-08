#pragma once

#include <stdint.h>
#include "../tinyasm/tinyasm.hpp"

#define MAX_HEAP_SIZE  1000
#define MAX_STACK_SIZE 1000
#define MAX_TXT_SIZE 1000

class cpu
{
public:

    /* no reason for the heap or stack to be in a cpu class, but it might as well be here temporarily */
    int16_t    heap[MAX_HEAP_SIZE]   = { 0 };
    int16_t    stack[MAX_STACK_SIZE] = { 0 };
    tasm::ins  txt[MAX_TXT_SIZE];
    
    enum _r { IP, SP, FP, ROP, EF, A, B, C };
    int16_t r[8] = { 0 };


    void single_step(tasm::ins& ins);
    void execute_all(int16_t start_ip);
    void debug_info();
};