#include "helpers.hpp"

/* Reads the entire contents of a file and writes it to a string */
std::string getStringFromFile(std::string filename) {
	std::ifstream file(filename);
	std::stringstream buffer;
	std::string str = "";

	if (!file.is_open()) {
		std::cout << "An error occurred while opening " << filename << std::endl;
		exit(-1);
	}
	else {
		buffer << file.rdbuf();
		str = buffer.str();
		if (str == "") std::cout << "The specified file " << filename << " is empty" << std::endl;
		file.close();
	}
	return str;
}

/* Check if all characters in string are unique */
bool isUnique(std::string str) {
	std::string temp = str;
	std::sort(temp.begin(), temp.end());
	return std::unique(temp.begin(), temp.end()) == temp.end();
}

/* Check if alphabet contains character c */
bool isInAlphabet(char& c, std::string alphabet) { return alphabet.find(c) != std::string::npos; }
