#include "LCG.hpp"

LCG::LCG() {
	this->modulus = 4294967296;
	this->multiplier = 1664525;
	this->increment = 1;
}

LCG::LCG(unsigned long long multiplier, unsigned long long increment, unsigned long long modulus) {
	// Check if multiplier is even
	if (multiplier % 2 == 0) {
		std::cout << "Multiplier (a) must be an odd number!";
		exit(-1);
	}

	// Check if modulus prime number or equals to 2^n
	if (!isPrime(modulus) && !isPowerOfTwo(modulus)) {
		std::cout << "Modulus (m) must be prime or to the power of 2!";
		exit(-1);
	}
	
	// Check if gcd(increment, modulus) == 1
	if (gcd(increment, modulus) != 1) {
		std::cout << "Increment (b) must be coprime with the modulus!";
		exit(-1);
	}

	this->multiplier = multiplier;
	this->increment = increment;
	this->modulus = modulus;
}

std::bitset<224> LCG::generate(std::bitset<32> input) {
	unsigned long long x = input.to_ullong();
	std::string bits = "";
	// Calculate the next number and translate it into 32 bits 7 times. A total of 224 bits are generated.
	for (int i = 0; i < 7; i++) {
		bits += std::bitset<32>(x).to_string();
		x = (multiplier * x + increment) % modulus;
	}
	return std::bitset<224>(bits);
}
