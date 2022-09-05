#ifndef AFFINE_HPP
#define AFFINE_HPP

#include "helpers.hpp"
#include <numeric>

class Affine {
private:
	std::string alphabet_ = "";
	std::string convertedAlphabet_ = "";
	unsigned short a_ = 0, b_ = 0;
public:
	Affine(std::string alphabet_filename, unsigned short a, unsigned short b);
	Affine(std::string alphabet);
	void encrypt(std::string message, std::string filename);
	void convertAlphabet();

	std::string getAlphabet() { return alphabet_; };
	std::string getConvertedAlpabet() { return convertedAlphabet_; };
	unsigned short getA() { return a_; };
	unsigned short getB() { return b_; };

	void setAlphabet(std::string alphabet) { alphabet_ = alphabet; };
	void setConvertedAlphabet(std::string convertedAlphabet) { convertedAlphabet_ = convertedAlphabet; };
	void setA(unsigned short a) { a_ = a; };
	void setB(unsigned short b) { b_ = b; };
};

#endif // !AFFINE_HPP
