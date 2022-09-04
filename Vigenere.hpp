#ifndef VIGENERE_HPP
#define VIGENERE_HPP

#include "helpers.hpp"

class Vigenere {
private:
	std::string alphabet_;
	std::string keyword_;

public:
	Vigenere(std::string alphabet_filename, std::string keyword_filename);
	void encrypt(std::string message, std::string filename);
	void decrypt(std::string encrypted_filename, std::string decrypted_filename);

	std::string getAlphabet() { return alphabet_; };
	std::string getKeyword() { return keyword_; };

	void setAlphabet(std::string alphabet) { alphabet_ = alphabet; };
	void setKeyword(std::string keyword) { keyword_ = keyword; };
};

#endif // !VIGENERE_HPP
