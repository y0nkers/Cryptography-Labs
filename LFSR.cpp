#include "LFSR.hpp"

LFSR::LFSR() {
	bits = std::bitset<17>("00000000000000000");
	relations = std::bitset<16>("0000000000000000");
}

LFSR::LFSR(std::string key_filename, std::string relations_filename) {
	std::string key = getStringFromFile(key_filename);
	if (key.size() != 17) {
		std::cout << "Error: LFSR key must must be 17 characters long." << std::endl;
		exit(-1);
	}

	std::string relations = getStringFromFile(relations_filename);
	if (relations.size() != 16) {
		std::cout << "Error: LFSR relations must must be 16 characters long." << std::endl;
		exit(-1);
	}

	try {
		bits = std::bitset<17>(key);
		this->relations = std::bitset<16>(relations);
	}
	catch (std::exception& e) {
		std::cout << "Error: invalid key characters" << std::endl;
		exit(-1);
	}
}

int LFSR::XOR() {
	int result = bits[0];
	for (int i = 0; i < relations.size(); i++)
		if (relations[i]) result ^= bits[i + 1];
	return result;
}

std::bitset<32> LFSR::generate() {
	std::bitset<32> generated;
	for (int i = 0; i < 32; i++) {
		//int left_bit = bits[16] ^ bits[13];
		int result = XOR();
		generated[i] = result;
		bits >>= 1;
		bits[16] = result;
	}
	return generated;
}
