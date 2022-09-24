#include "LCG.hpp"

LCG::LCG() {
	modulus = 4294967296;
	multiplier = 1664525;
	increment = 1;
}

LCG::LCG(unsigned long long mp, unsigned long long incr, unsigned long long mod) {
	// Check if multiplier is even
	if (mp % 2 == 0) {
		std::cout << "Multiplier (a) must be an odd number!";
		exit(-1);
	}

	// Check if modulus prime number or equals to 2^n
	if (!isPrime(mod) && !isPowerOfTwo(mod)) {
		std::cout << "Modulus (m) must be prime or to the power of 2!";
		exit(-1);
	}
	
	// Check if gcd(increment, modulus) == 1
	if (gcd(incr, mod) != 1) {
		std::cout << "Increment (b) must be coprime with the modulus!";
		exit(-1);
	}

	multiplier = mp;
	increment = incr;
	modulus = mod;
}

boost::dynamic_bitset<> LCG::generate(std::bitset<32> input, int amount) {
	unsigned long long x = input.to_ullong();
	std::string bits = "";
	// Calculate the next number and translate it into 32 bits times. A total of (32 * amount) bits are generated.
	for (int i = 0; i < amount; i++) {
		bits += std::bitset<32>(x).to_string();
		x = (multiplier * x + increment) % modulus;
	}
	return boost::dynamic_bitset<>(bits);
}
