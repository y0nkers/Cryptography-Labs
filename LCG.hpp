#ifndef LCG_HPP
#define LCG_HPP

#include "helpers.hpp"

// Linear Congruential Generator [generates pseudo-randomized numbers calculated with linear equation Y = (a * X + b) mod m]
class LCG {
private:
	unsigned long long modulus; // m - modulus in equation (by default equals to 2^32)
	unsigned long long multiplier; // a - multiplier in equation (recommend 40692, 1664525 or 6364136223846793005)
	unsigned long long increment; // b - increment in equation
public:
	LCG();
	LCG(unsigned long long multiplier, unsigned long long increment, unsigned long long modulus = 4294967296);
	std::bitset<224> generate(std::bitset<32> input);
};

#endif // !LCG_HPP
