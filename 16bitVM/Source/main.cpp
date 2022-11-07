#include <iostream>
#include <fstream>

#include "cpu/cpu.hpp"
#include "tinyasm/tinyasm.hpp"
#include "tinyasm/assembler/assembler.hpp"

int main()
{


    cpu CPU;
    assemble assembler;
    std::vector<tasm::ins> ins_buffer = assembler.file("C:\\Users\\user\\Desktop\\16bitVM\\16bitVM\\Source\\example.ta");

    for (int i = 0; i < ins_buffer.size(); i++)
    {
        CPU.txt[i] = ins_buffer[i];
    }

    CPU.execute_all(0);

}

