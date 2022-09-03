#include "helpers.hpp"

/* Reads the entire contents of a file and writes it to a string */
std::string getStringFromFile(std::string filename) {
	std::ifstream file(filename);
	std::stringstream buffer;
	std::string str = "";

	if (!file.is_open()) {
		std::cout << "An error occurred while opening " << filename << std::endl;
	}
	else {
		buffer << file.rdbuf();
		str = buffer.str();
		if (str == "") std::cout << "The specified file " << filename << " is empty" << std::endl;
		file.close();
	}
	return str;
}
