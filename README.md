# 16bitVM - Runs arbritrary arbitrary bytecode
There's no particular reason for this "VM" to be 16-bit, as you could just as easily change the types from int16_t to int64_t, but it just
seemed easier to work with. Uses a homebrewed assembly-esque language "tinyasm.hpp" which gets compiled into bytecode before getting executed.
Uses fixed width instructions and currently lacks any proper memory management structure. 

-  `"../Source/tinyasm/tinyasm.hpp" `
  Basic instruction structure, TODO : add docs
-  `"../Source/tinyasm/assembler/assembler.cpp `
  Assembles an instruction file into the bytecode
-  `"../Source/cpu/cpu.cpp" > void cpu::single_step(tasm::ins& ins); `
  Executes a single instruction
  -  `"../Source/cpu/cpu.cpp" > void cpu::single_step(tasm::ins& ins); `
  Executes a single instruction and INCREMENTS IP.
  -  `"../Source/cpu/cpu.cpp" > void cpu::execute_all(int16_t start_ip); `
  Executes a buffer of instructions from the .txt section ( which is currently still contained in the CPU class due to lack of full structure )
   from the instruction pointer it's called with. Simply repeatedly single steps the cpu untill an exception is raised. 

Example pseudocode:
```cpp
 void main()
{
	int x = 3;
	int y = 4;
	int z = multiply_togheter_then_by_two(x, y);
	/* BREAKPOINT HERE */
}


int multiply_togheter_then_by_two(int a, int b)
{
	return (a * b) * 2;
}
```

Converted to tinyasm and ready to execute
```
PUSH i3;
PUSH i4;
NOP;
NOP;
PUSH f0;
PUSH f1;
CALL r10;
POP;
POP;
PUSH r3;
INT3;
NOP;
NOP;
NOP;
NOP;
NOP;
MULT f-2, f-3;
MULT r3, i2;
RET;
```

