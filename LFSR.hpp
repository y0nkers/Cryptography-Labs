#ifndef LFSR_HPP
#define LFSR_HPP

#include "helpers.hpp"

class LFSR {
private:
	std::bitset<17> bits;
	std::bitset<16> relations;
	int XOR();
public:
	LFSR(std::string key_filename, std::string relations_filename);
	std::bitset<32> generate();
};

#endif // !LFSR_HPP
