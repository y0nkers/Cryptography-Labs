#include "CaesarWithKeyword.hpp"

CaesarWithKeyword::CaesarWithKeyword(std::string alphabet_filename, std::string keyword_filename, unsigned short key) : digitKey_(key) {
	alphabet_ = getStringFromFile(alphabet_filename);
	keyword_ = getStringFromFile(keyword_filename);

	if (!isUnique(alphabet_)) {
		std::cout << "Characters in the alphabet are not unique!" << std::endl;
		exit(-1);
	}

	for (char& c : keyword_) {
		if (!isInAlphabet(c, alphabet_)) {
			std::cout << "One of the keyword characters is not in the alphabet!" << std::endl;
			exit(-1);
		}
	}

	if (!isUnique(keyword_)) {
		std::cout << "Characters in the keyword are not unique!" << std::endl;
		exit(-1);
	}
}

void CaesarWithKeyword::encrypt(std::string message, std::string filename) {
	std::string encrypted_message = "";

	for (auto&& c : message)
		encrypted_message += convertedAlphabet_[alphabet_.find(c)];

	std::ofstream encrypted_file(filename);
	encrypted_file << encrypted_message;
	encrypted_file.close();
	std::cout << "Message successfully encrypted and written to file " << filename << "." << std::endl;
}

void CaesarWithKeyword::decrypt(std::string encrypted_filename, std::string decrypted_filename) {
	std::string encrypted_message = getStringFromFile(encrypted_filename);
	std::string decrypted_message = "";

	for (auto&& c : encrypted_message)
		decrypted_message += alphabet_[convertedAlphabet_.find(c)];

	std::ofstream decrypted_file(decrypted_filename);
	decrypted_file << decrypted_message;
	decrypted_file.close();
	std::cout << "Message successfully decrypted and written to file " << decrypted_filename << "." << std::endl;
}

void CaesarWithKeyword::convertAlphabet() {
	unsigned short alphabetLength = alphabet_.length();
	convertedAlphabet_.resize(alphabetLength, '0');

	// write the keyword under the index of the digit key
	unsigned short key_index = digitKey_;
	for (char& c : keyword_) {
		convertedAlphabet_[key_index++ % alphabetLength] = c;
	}

	key_index %= alphabetLength;

	// write old alphabet after keyword
	unsigned short currAlphIdx = 0;
	for (key_index; key_index < alphabetLength; key_index++) {
		for (currAlphIdx; currAlphIdx < alphabetLength; currAlphIdx++) {
			// if alphabet[currAlphIdx] is not found in keyword, we writing it in convertedAlphabet after keyword
			if (!(keyword_.find(alphabet_[currAlphIdx]) != std::string::npos)) {
				convertedAlphabet_[key_index] = alphabet_[currAlphIdx++];
				break;
			}
		}
	}

	if (currAlphIdx == alphabetLength) return;
	// write the remaining characters of the old alphabet before the keyword
	for (unsigned short i = 0; i < digitKey_; i++) {
		for (currAlphIdx; currAlphIdx < alphabetLength; currAlphIdx++) {
			if (!(keyword_.find(alphabet_[currAlphIdx]) != std::string::npos)) {
				convertedAlphabet_[i] = alphabet_[currAlphIdx++];
				break;
			}
		}
	}
}
