#pragma once
#include "Token.hpp"
#include <string_view>
#include <vector>

std::vector<Token>
lex(std::string_view src);
