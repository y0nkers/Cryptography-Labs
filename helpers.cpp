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

/* Find Greatest Common Divisor of 2 numbers with Euclidean algorithm */
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

/* Check if given number is prime */
bool isPrime(unsigned long long n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (int i = 3; (i * i) <= n; i += 2)
		if (n % i == 0) return false;
	return true;
}

/* Check if given number is a power of 2 */
bool isPowerOfTwo(unsigned long long n) { return (n > 0 && ((n & (n - 1)) == 0)); }
