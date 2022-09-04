#include "SimpleEncryptionTables.hpp"

SimpleEncryptionTables::SimpleEncryptionTables(unsigned short rowsCount, unsigned short columnsCount) : rows_(rowsCount), columns_(columnsCount) {}

void SimpleEncryptionTables::encrypt(std::string message, std::string filename) {
	unsigned short tableCount = ceil(message.length() / (rows_ * columns_ * 1.0));
	unsigned short elementsCount = tableCount * rows_ * columns_;

	// new string with a length equal to the number of elements in the tables
	std::string encrypted_message(elementsCount, ' ');
	// if the length of the message is less than the number of elements in the tables, then we add spaces to the end of the message
	if (message.length() < elementsCount) message.append(elementsCount - message.length(), ' ');

	unsigned short idx = 0;
	for (unsigned short i = 0; i < tableCount; i++) {
		for (unsigned short column = 0; column < columns_; column++) {
			for (unsigned short row = 0; row < rows_; row++) {
				encrypted_message[row * columns_ + column] = message[idx++];
			}
		}
	}

	std::ofstream encrypted_file(filename);
	encrypted_file << encrypted_message;
	encrypted_file.close();
	std::cout << "Message successfully encrypted and written to file " << filename << "." << std::endl;
}

void SimpleEncryptionTables::decrypt(std::string encrypted_filename, std::string decrypted_filename) {
	std::string encrypted_message = getStringFromFile(encrypted_filename);
	if (encrypted_message == "") {
		std::cout << encrypted_filename << " is empty!" << std::endl;
		exit(-1);
	}

	unsigned short tableCount = encrypted_message.length() / (rows_ * columns_);
	unsigned short elementsCount = tableCount * rows_ * columns_;
	std::string decrypted_message(elementsCount, ' ');

	unsigned short idx = 0;
	for (unsigned short i = 0; i < tableCount; i++) {
		for (unsigned short column = 0; column < columns_; column++) {
			for (unsigned short row = 0; row < rows_; row++) {
				decrypted_message[idx++] = encrypted_message[row * columns_ + column];
			}
		}
	}

	// Right trim whitespaces
	decrypted_message.erase(std::find_if(decrypted_message.rbegin(), decrypted_message.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), decrypted_message.end());

	std::ofstream decrypted_file(decrypted_filename);
	decrypted_file << decrypted_message;
	decrypted_file.close();
	std::cout << "Message successfully encrypted and written to file " << decrypted_filename << "." << std::endl;
}
