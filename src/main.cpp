#include "Lexer.hpp"
#include <fstream>
#include <iostream>

int
main(int argc, char** args)
{
	std::ifstream file("test.cflang", std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string buffer;
	buffer.resize(size);
	file.read(buffer.data(), size);

	auto tokens = lex(buffer);

	for (auto& token : tokens) {
		std::cout << token.to_string(buffer) << "\n";
	}

	return 0;
}
