#ifndef CAESAR_HPP
#define CAESAR_HPP

#include "helpers.hpp"

class CaesarWithKeyword {
private:
	std::string alphabet_;
	std::string convertedAlphabet_ = "";
	std::string keyword_;
	unsigned short digitKey_ = 0;

public:
	CaesarWithKeyword(std::string alphabet_filename, std::string keyword_filename, unsigned short key);
	void encrypt(std::string message, std::string filename);
	void decrypt(std::string encrypted_filename, std::string decrypted_filename);
	void convertAlphabet();

	std::string getAlphabet() { return alphabet_; };
	std::string getConvertedAlpabet() { return convertedAlphabet_; };
	std::string getKeyword() { return keyword_; };
	unsigned short getDigitKey() { return digitKey_; };

	void setAlphabet(std::string alphabet) { alphabet_ = alphabet; };
	void setConvertedAlphabet(std::string convertedAlphabet) { convertedAlphabet_ = convertedAlphabet; };
	void setKeyword(std::string keyword) { keyword_ = keyword; };
	void setDigitKey(unsigned short key) { digitKey_ = key; };
};

#endif // !CAESAR_HPP
