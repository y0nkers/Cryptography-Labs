#include "Generator.hpp"

Generator::Generator(LFSR *stage1, LCG *stage2) {
	lfsr = stage1;
	lcg = stage2;
}

/* Converts bits to letters using charactersTable map */
std::string Generator::bitsToString(boost::dynamic_bitset<> bits) {
	std::string output = "";
	int index = bits.size() - 1;
	// Getting a letter from next 5 bits
	while (index >= 4) {
		std::string letter = "";
		for (int j = 0; j < 5; j++) {
			// If current bit is set we write 1 in letter, otherwise 0
			if (bits.test(index--)) letter += "1";
			else letter += "0";
		}

		// After that, in the charactersTable we find the key of this letter by value
		for (auto it = charactersTable.begin(); it != charactersTable.end(); ++it) {
			if (it->second == letter) {
				output += it->first;
				break;
			}
		}
	}

	return output;
}

/* Converts letters to bits using charactersTable map */
boost::dynamic_bitset<> Generator::stringToBits(std::string str) {
	std::string str_bits = "";
	for (int i = 0; i < str.length(); i++)
		str_bits += charactersTable.find(str[i])->second;
	return boost::dynamic_bitset<>(str_bits);
}

/* Get gamma for encrypting a message */
boost::dynamic_bitset<> Generator::getGamma(std::string message) {
	int length = message.length() * 5; // Each message character is encoded with 5 bits
	std::string gamma_str = "";

	while (length > 0) {
		std::bitset<32> lfsr_output = lfsr->generate();
		std::bitset<224> lcg_output = lcg->generate(lfsr_output);
		gamma_str += lcg_output.to_string();
		length -= 224;
	}
	gamma_str = gamma_str.substr(0, message.length() * 5);
	return boost::dynamic_bitset<>(gamma_str);
}

void Generator::encrypt(std::string message, std::string filename) {
	boost::dynamic_bitset<> gamma = getGamma(message);
	boost::dynamic_bitset<> msg = stringToBits(message);
	boost::dynamic_bitset<> encrypted(gamma);
	encrypted.operator^=(msg);
	
	std::cout << std::endl << "Message to Encrypt: " << std::endl << bitsToString(msg) << std::endl;
	std::cout << "Generated Gamma:" << std::endl << bitsToString(gamma) << std::endl;

	std::cout << std::endl << "Message bits: " << std::endl << msg << std::endl;
	std::cout << "Gamma bits: " << std::endl << gamma << std::endl;

	std::cout << std::endl << "Result of Message XOR Gamma:" << std::endl << encrypted << std::endl;
	std::cout << "Encrypted message: " << std::endl << bitsToString(encrypted) << std::endl;

	std::ofstream encrypted_file(filename);
	encrypted_file << bitsToString(encrypted);
	encrypted_file.close();
	std::cout << std::endl << "Message successfully encrypted and written to file " << filename << "." << std::endl;
}

void Generator::decrypt(std::string encrypted_filename, std::string decrypted_filename) {
	std::string encrypted_message = getStringFromFile(encrypted_filename);

	boost::dynamic_bitset<> gamma = getGamma(encrypted_message);
	boost::dynamic_bitset<> encrypted = stringToBits(encrypted_message);
	boost::dynamic_bitset<> decrypted(gamma);
	decrypted.operator^=(encrypted);

	std::cout << std::endl << "Message to Decrypt: " << std::endl << encrypted_message << std::endl;
	std::cout << "Generated Gamma:" << std::endl << bitsToString(gamma) << std::endl;

	std::cout << std::endl << "Message bits: " << std::endl << encrypted << std::endl;
	std::cout << "Gamma bits: " << std::endl << gamma << std::endl;

	std::cout << std::endl << "Result of Message XOR Gamma:" << std::endl << decrypted << std::endl;
	std::cout << "Decrypted message: " << std::endl << bitsToString(decrypted) << std::endl;

	std::ofstream decrypted_file(decrypted_filename);
	decrypted_file << bitsToString(decrypted);
	decrypted_file.close();
	std::cout << "Message successfully decrypted and written to file " << decrypted_filename << "." << std::endl;
}
