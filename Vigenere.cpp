#include "Vigenere.hpp"

Vigenere::Vigenere(std::string alphabet_filename, std::string keyword_filename) {
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
}

void Vigenere::encrypt(std::string message, std::string filename) {
	std::string encrypted_message = "";

	unsigned short currKeyIdx = 0;
	for (int i = 0; i < message.length(); i++) {
		// In the alphabet, find the current character of the encrypted message, which is shifted by a number equal to the position of the current character of the keyword. Do not forget to take modulo the length of the alphabet, so as not to go beyond.
		encrypted_message += alphabet_[(alphabet_.find(message[i]) + alphabet_.find(keyword_[currKeyIdx++ % keyword_.length()])) % alphabet_.length()];
	}

	std::ofstream encrypted_file(filename);
	encrypted_file << encrypted_message;
	encrypted_file.close();
	std::cout << "Message successfully encrypted and written to file " << filename << "." << std::endl;
}

void Vigenere::decrypt(std::string encrypted_filename, std::string decrypted_filename) {
	std::string encrypted_message = getStringFromFile(encrypted_filename);
	std::string decrypted_message = "";

	unsigned short currKeyIdx = 0;
	for (int i = 0; i < encrypted_message.length(); i++) {
		int cipher_idx = alphabet_.find(encrypted_message[i]);
		int key_idx = alphabet_.find(keyword_[currKeyIdx++ % keyword_.length()]);
		// If the keyword character is further than the encrypted message character, then we go to the beginning of the alphabet and "exit" at the other end.
		if (cipher_idx < key_idx) decrypted_message += alphabet_[alphabet_.length() - abs(cipher_idx - key_idx)];
		else decrypted_message += alphabet_[(cipher_idx - key_idx) % alphabet_.length()];
	}

	std::ofstream decrypted_file(decrypted_filename);
	decrypted_file << decrypted_message;
	decrypted_file.close();
	std::cout << "Message successfully decrypted and written to file " << decrypted_filename << "." << std::endl;
}
