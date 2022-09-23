#include "Generator.hpp"

Generator::Generator(LFSR *lfsr, LCG *lcg) {
	this->lfsr = lfsr;
	this->lcg = lcg;
}

void Generator::encrypt(std::string message, std::string filename) {
	int length = message.length() * 5;
	std::string gamma_str = "";
	while (length > 0) {
		std::bitset<32> lfsr_output = lfsr->generate();
		std::bitset<224> lcg_output = lcg->generate(lfsr_output);
		gamma_str += lcg_output.to_string();
		length -= 224;
	}
	gamma_str = gamma_str.substr(0, message.length() * 5);
	int i = 1;
	boost::dynamic_bitset<> gamma(gamma_str);

	// Convert message in binary using charactersTable
	std::string msg_bits = "";
	for (int i = 0; i < message.length(); i++)
		msg_bits += charactersTable.find(message[i])->second;

	boost::dynamic_bitset<> msg(msg_bits);
	boost::dynamic_bitset<> temp(gamma);
	temp.operator^=(msg);
	
	std::cout << "MESSAGE BITS:" << std::endl << msg << std::endl;
	// todo: add method for convert binary to string using charactersTable
	std::cout << "GAMMA BITS:" << std::endl << gamma << std::endl;
	std::cout << "MESSAGE XOR GAMMA:" << std::endl << temp << std::endl;

	std::ofstream encrypted_file(filename);
	encrypted_file << temp;
	encrypted_file.close();
	std::cout << "Message successfully encrypted and written to file " << filename << "." << std::endl;
}
