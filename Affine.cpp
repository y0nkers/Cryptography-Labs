#include "Affine.hpp"

Affine::Affine(std::string alphabet_filename, unsigned short a, unsigned short b) : a_(a), b_(b) {
	alphabet_ = getStringFromFile(alphabet_filename);

	if (!isUnique(alphabet_)) {
		std::cout << "Characters in the alphabet are not unique!" << std::endl;
		exit(-1);
	}

	if (gcd(a, alphabet_.length()) != 1) {
		std::cout << "The Greatest Common Divisor of the key A and the number of letters in the alphabet must be equal to one!" << std::endl;
		exit(-1);
	}
}

Affine::Affine(std::string alphabet) {
	alphabet_ = alphabet;
}

void Affine::encrypt(std::string message, std::string filename) {
	std::string encrypted_message = "";

	for (auto&& c : message)
		encrypted_message += convertedAlphabet_[alphabet_.find(c)];

	std::ofstream encrypted_file(filename);
	encrypted_file << encrypted_message;
	encrypted_file.close();
	std::cout << "Message successfully encrypted and written to file " << filename << "." << std::endl;
}

void Affine::decrypt(std::string encrypted_filename, std::string decrypted_filename) {
	std::string encrypted_message = getStringFromFile(encrypted_filename);
	std::string decrypted_message = "";

	for (auto&& c : encrypted_message)
		decrypted_message += alphabet_[convertedAlphabet_.find(c)];

	std::ofstream decrypted_file(decrypted_filename);
	decrypted_file << decrypted_message;
	decrypted_file.close();
	std::cout << "Message successfully decrypted and written to file " << decrypted_filename << "." << std::endl;
}

void Affine::convertAlphabet() {
	unsigned short alphabetLength = alphabet_.length();
	convertedAlphabet_.resize(alphabetLength, '0');
	
	for (unsigned short i = 0; i < alphabetLength; i++)
		convertedAlphabet_[i] = alphabet_[(a_ * i + b_) % alphabetLength];
}
