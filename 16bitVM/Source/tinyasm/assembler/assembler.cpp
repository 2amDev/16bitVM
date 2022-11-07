#include "assembler.hpp"

#include <fstream>
#include <map>

namespace
{
	std::map<std::string, tasm::op> opcode_name_to_enum =
	{
		{"NOP",  tasm::op::NOP},
		{"ADD",  tasm::op::ADD},
		{"SUB",  tasm::op::SUB},
		{"MULT", tasm::op::MULT},
		{"CMP",  tasm::op::CMP},
		{"MOV",  tasm::op::MOV},
		{"JMP",  tasm::op::JMP},
		{"JNZ",  tasm::op::JNZ},
		{"JZ",   tasm::op::JZ},
		{"PUSH", tasm::op::PUSH},
		{"POP",  tasm::op::POP},
		{"CALL", tasm::op::CALL},
		{"RET",  tasm::op::RET},
		{"INT3",  tasm::op::INT3}
	};
	std::map<char, tasm::cntr> char_to_cntr_flag =
	{
		{'i', tasm::cntr::D},
		{'r', tasm::cntr::R},
		{'p', tasm::cntr::P},
		{'f', tasm::cntr::RFP},
		{'s', tasm::cntr::RSP}
	};
}


tasm::ins assemble::single(std::string single_instruction)
{
	tasm::ins interpreted;
	std::string opcode_as_string = single_instruction.substr(0, single_instruction.find(' '));
	interpreted.opcode = opcode_name_to_enum[opcode_as_string];

    switch (interpreted.opcode)
    {
    case tasm::op::NOP:
        break;
    case tasm::op::ADD:
    case tasm::op::SUB:
    case tasm::op::MULT:
    case tasm::op::CMP:
    case tasm::op::MOV:
		interpreted.cf[0] = char_to_cntr_flag[single_instruction[single_instruction.find(' ') + 1]];
		interpreted.cf[1] = char_to_cntr_flag[single_instruction[single_instruction.find(',') + 2]];
		interpreted.v[0] = std::stoi(single_instruction.substr(single_instruction.find(' ') + 2, single_instruction.find(',') - (single_instruction.find(' ') + 2)));
		interpreted.v[1] = std::stoi(single_instruction.substr(single_instruction.find(',') + 3, single_instruction.size() - (single_instruction.find(',') + 2)));
        break;
    case tasm::op::JMP:
    case tasm::op::JNZ:
    case tasm::op::JZ:
		interpreted.cf[0] = (tasm::cntr)(single_instruction[single_instruction.find(' ') + 1] == 'a');
		interpreted.v[0] = std::stoi(single_instruction.substr(single_instruction.find(' ') + 2, single_instruction.size() - (single_instruction.find(' ') + 2)));
        break;
    case tasm::op::PUSH:
		interpreted.v[0] = std::stoi(single_instruction.substr(single_instruction.find(' ') + 2, single_instruction.size() - (single_instruction.find(' ') + 2)));
        break;
    case tasm::op::POP:
        break;
    case tasm::op::CALL:
		interpreted.cf[0] = (tasm::cntr)(single_instruction[single_instruction.find(' ') + 1] == 'a');
		interpreted.v[0] = std::stoi(single_instruction.substr(single_instruction.find(' ') + 2, single_instruction.size() - (single_instruction.find(' ') + 2)));
        break;
	case tasm::op::RET:
        break;
	case tasm::op::INT3:
		break;
    }
		
	return interpreted;
}
std::vector<tasm::ins> assemble::buffer(std::string series_instruction)
{
	std::vector<tasm::ins> interpreted_buffer;

	int16_t IP = 0;
	for (int i = 0; series_instruction[i] != '\0'; i++)
	{
		std::string current_instruction;
		for (int j = 0; series_instruction[i + j] != '\0'; j++)
		{
			if (series_instruction[i + j] != ';')
			{
				current_instruction += series_instruction[i + j];
			}
			else
			{
				i = i + j;
				break;
			}
		}
		IP++;
		interpreted_buffer.push_back(assemble::single(current_instruction));
	}

	return interpreted_buffer;
}
std::vector<tasm::ins> assemble::file(std::string filepath)
{
	std::ifstream ifs(filepath);
	std::string raw_content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	std::string content_no_newline;
	for (char i : raw_content)
		if (i != '\n')
			content_no_newline += i;

	return assemble::buffer(content_no_newline);
}