#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "LFSR.hpp"
#include "LCG.hpp"

// Two-stage pseudo-random number generator. Stage I - Linear Feedback Shift Register, Stage II - Linear Congruential Generator.
class Generator {
private:
	// ABCDEFGHIJKLMNOPQRSTUVWXYZ ,.!?-  32 characters total = 5 bits per character
	std::unordered_map<char, std::string> charactersTable = {
		{'A', "00000"},
		{'B', "00001"},
		{'C', "00010"},
		{'D', "00011"},
		{'E', "00100"},
		{'F', "00101"},
		{'G', "00110"},
		{'H', "00111"},
		{'I', "01000"},
		{'J', "01001"},
		{'K', "01010"},
		{'L', "01011"},
		{'M', "01100"},
		{'N', "01101"},
		{'O', "01110"},
		{'P', "01111"},
		{'Q', "10000"},
		{'R', "10001"},
		{'S', "10010"},
		{'T', "10011"},
		{'U', "10100"},
		{'V', "10101"},
		{'W', "10110"},
		{'X', "10111"},
		{'Y', "11000"},
		{'Z', "11001"},
		{' ', "11010"},
		{',', "11011"},
		{'.', "11100"},
		{'!', "11101"},
		{'?', "11110"},
		{'-', "11111"}
	};
	LFSR *lfsr;
	LCG *lcg;

	std::string bitsToString(boost::dynamic_bitset<> bits);
	boost::dynamic_bitset<> stringToBits(std::string str);
	boost::dynamic_bitset<> getGamma(std::string message);
public:
	Generator(LFSR *lfsr, LCG *lcg);
	void encrypt(std::string message, std::string filename);
	void decrypt(std::string encrypted_filename, std::string decrypted_filename);
};

#endif // !GENERATOR_HPP