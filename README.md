# 16bitVM - Runs arbritrary arbitrary bytecode
There's no particular reason for this "VM" to be 16-bit, as you could just as easily change the types from int16_t to int64_t, but it just
seemed easier to work with. Uses a homebrewed assembly-esque language "tinyasm.hpp" which gets compiled into bytecode before getting executed.
Uses fixed width instructions and currently lacks any proper memory management structure. 

- "../Source/tinyasm/tinyasm.hpp"
  Basic instruction structure, TODO : add docs and explain instruction structure
- "../Source/tinyasm/assembler/assembler.hpp & assembler.cpp
  Assembles an instruction file into the bytecode
- "../Source/cpu/cpu.cpp" > void cpu::single_step(tasm::ins& ins);
  Executes a single instruction
  - "../Source/cpu/cpu.cpp" > void cpu::single_step(tasm::ins& ins);
  Executes a single instruction and INCREMENTS IP.
  - "../Source/cpu/cpu.cpp" > void cpu::execute_all(int16_t start_ip);
  Executes a buffer of instructions from the .txt section ( which is currently still contained in the CPU class due to lack of full structure )
   from the instruction pointer it's called with. Incredibly simple and just repeatedly single steps the cpu, looks as follows : 
```cpp
void cpu::execute_all(int16_t start_ip)
{
    r[IP] = start_ip;
    while (!r[EF])
    {
        single_step(txt[r[IP]]);
    }

    debug_info();
} 
```
