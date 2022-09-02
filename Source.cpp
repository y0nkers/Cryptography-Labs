#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

std::string getConvertedAlphabet(std::string alphabet, std::string keyword, unsigned short digitKey) {
	unsigned short alphabetLength = alphabet.length();
	std::string convertedAlphabet(alphabetLength, '0');

	// write the keyword under the index of the digit key
	unsigned short key_index = digitKey;
	for (char& c : keyword) {
		convertedAlphabet[key_index++ % alphabetLength] = c;
	}

	key_index %= alphabetLength;

	// write old alphabet after keyword
	unsigned short currAlphIdx = 0;
	for (key_index; key_index < alphabetLength; key_index++) {
		for (currAlphIdx; currAlphIdx < alphabetLength; currAlphIdx++) {
			// if alphabet[j] is not found in keyword, we writing it in convertedAlphabet after keyword
			if (!(keyword.find(alphabet[currAlphIdx]) != std::string::npos)) {
				convertedAlphabet[key_index] = alphabet[currAlphIdx];
				currAlphIdx++;
				break;
			}
		}
	}

	if (currAlphIdx == alphabetLength) return convertedAlphabet;
	// write the remaining characters of the old alphabet before the keyword
	for (unsigned short i = 0; i < keyword.length(); i++) {
		for (currAlphIdx; currAlphIdx < alphabetLength; currAlphIdx++) {
			if (!(keyword.find(alphabet[currAlphIdx]) != std::string::npos)) {
				convertedAlphabet[i] = alphabet[currAlphIdx];
				currAlphIdx++;
				break;
			}
		}
	}

	return convertedAlphabet;
}

void Encrypt(std::string message, std::string alphabet, std::string convertedAlphabet)
{
	std::ofstream encrypted_file("encrypted.txt");
	std::string encrypted_message = "";

	for (auto&& c : message) 
		encrypted_message += convertedAlphabet[alphabet.find(c)];

	encrypted_file << encrypted_message;
	encrypted_file.close();
}

bool Decrypt(std::string alphabet, std::string convertedAlphabet)
{
	std::ifstream encrypted_file("encrypted.txt");
	std::stringstream encrypted_buffer;
	std::string encrypted_string;

	if (!encrypted_file.is_open()) {
		std::cout << "An error occurred while opening the encrypted file" << std::endl;
		return -1;
	}
	else {
		encrypted_buffer << encrypted_file.rdbuf();
		encrypted_string = encrypted_buffer.str();
	}

	std::ofstream decrypted_file("decrypted.txt");
	std::string decrypted_message = "";

	for (auto&& c : encrypted_string)
		decrypted_message += alphabet[convertedAlphabet.find(c)];

	decrypted_file << decrypted_message;
	decrypted_file.close();
}

/* Check if all characters in string are unique */
bool isUnique(std::string str) {
	std::string temp = str;
	std::sort(temp.begin(), temp.end());
	return std::unique(temp.begin(), temp.end()) == temp.end();
}

bool isInAlphabet(char& c, std::string alphabet) { return alphabet.find(c) != std::string::npos; }

int main(int argv, char** argc) {
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ .,0123456789";

	// MESSAGE FILE

	std::ifstream message_file("message.txt");
	std::stringstream message_buffer;
	std::string message_string;

	if (!message_file.is_open()) {
		std::cout << "An error occurred while opening the message file" << std::endl;
		return -1;
	}
	else {
		message_buffer << message_file.rdbuf();
		message_string = message_buffer.str();
	}

	// KEY FILE

	std::ifstream key_file("key.txt");
	std::stringstream key_buffer;
	std::string key_string;

	if (!key_file.is_open()) {
		std::cout << "An error occurred while opening the key file" << std::endl;
		return -1;
	}
	else {
		key_buffer << key_file.rdbuf();
		key_string = key_buffer.str();

		for (char& c : key_string) {
			if (!isInAlphabet(c, alphabet)) {
				std::cout << "One of the key characters is not in the alphabet!" << std::endl;
				return -1;
			}
		}

		if (!isUnique(key_string)) {
			std::cout << "Characters in the key are not unique!" << std::endl;
			return -1;
		}

	}

	unsigned short digit_key = 0;

	do {
		std::cout << "Enter a digit key (0 <= K <= " << alphabet.length() - 1 << "): ";
		std::cin >> digit_key;
	} while ((digit_key < 0) || (digit_key > alphabet.length() - 1));

	std::string convertedAlphabet = getConvertedAlphabet(alphabet, key_string, digit_key);

	Encrypt(message_string, alphabet, convertedAlphabet);
	Decrypt(alphabet, convertedAlphabet);

	return 0;
}