#ifndef LFSR_HPP
#define LFSR_HPP

#include "helpers.hpp"

class LFSR {
private:
	std::bitset<17> bits;

	int XOR(int bit1, int bit2);
public:
	LFSR(std::string key_filename);
	std::bitset<32> generate();
};

#endif // !LFSR_HPP
