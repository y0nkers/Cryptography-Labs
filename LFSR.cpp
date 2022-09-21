#include "LFSR.hpp"

LFSR::LFSR(std::string key_filename) {
	std::string key = getStringFromFile(key_filename);
	if (key.size() != 17) {
		std::cout << "Error: LFSR key must must be 17 characters long." << std::endl;
		exit(-1);
	}

	try {
		bits = std::bitset<17>(key);
	}
	catch (std::exception& e) {
		std::cout << "Error: invalid key characters" << std::endl;
		exit(-1);
	}
}

int LFSR::XOR(int bit1, int bit2) { return bits[bit1] ^ bits[bit2]; }

std::bitset<32> LFSR::generate() {
	std::bitset<32> generated;
	for (int i = 0; i < 32; i++) {
		int left_bit = XOR(16, 13);
		generated[i] = bits[0];
		bits >>= 1;
		bits[16] = left_bit;
	}
	return generated;
}
