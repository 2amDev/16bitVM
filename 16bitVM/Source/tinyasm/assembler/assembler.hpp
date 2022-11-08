#pragma once

#include "../tinyasm.hpp"

#include <string>
#include <vector>

namespace assemble
{
    tasm::ins              single(std::string single_instruction);
    std::vector<tasm::ins> buffer(std::string series_instruction);
    std::vector<tasm::ins> file  (std::string filepath);
};