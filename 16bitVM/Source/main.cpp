#include <iostream>
#include <fstream>

#include "cpu/cpu.hpp"
#include "tinyasm/tinyasm.hpp"

int main()
{
    cpu CPU;

    for (int i = 0; i < 10; i++)
    {
        tasm::ins ins;
        ins.opcode = tasm::op::PUSH;
        ins.cf[0]  = tasm::cntr::D;
        ins.v[0]   = 5;
        CPU.txt[i] = ins;

        CPU.execute(CPU.txt[i]);

    }


    CPU.debug_info();


}

