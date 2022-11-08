#include <iostream>
#include <fstream>

#include "cpu/cpu.hpp"
#include "tinyasm/tinyasm.hpp"
#include "tinyasm/assembler/assembler.hpp"

int main()
{


    cpu CPU;

    std::vector<tasm::ins> ins_buffer = assemble::file("example.ta");

    for (int i = 0; i < ins_buffer.size(); i++)
        CPU.txt[i] = ins_buffer[i];

    CPU.execute_all(0);

}

