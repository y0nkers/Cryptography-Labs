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

void Affine::cryptoanalysis(std::string encrypted_filename, std::unordered_map<char, double> lettersStatistics) {
	std::string encrypted_message = getStringFromFile(encrypted_filename);

	// Vector for all possible A. gcd(A, alphabet.length) must be equal to one
	std::vector<unsigned short> A;
	for (unsigned short i = 1; i < alphabet_.length(); i++) if (gcd(i, alphabet_.length()) == 1) A.push_back(i);

	double diffMin = 0;
	bool firstCalculate = true;
	std::pair<unsigned short, unsigned short> keys; // (a, b)

	for (unsigned short a : A) {
		setA(a);
		for (unsigned short b = 0; b < alphabet_.length() - 1; b++) {
			// Setting up new key pair (a, b)
			setB(b);
			convertAlphabet();

			// Decrpyting encrypted message
			std::string decrypted_message = "";
			for (auto&& c : encrypted_message) decrypted_message += alphabet_[convertedAlphabet_.find(c)];

			// Count the number of each letter in the text
			std::vector<int> lettersCount(alphabet_.length(), 0);
			for (auto&& c : decrypted_message) lettersCount[alphabet_.find(c)]++;

			// Determine the probability of occurrence of each letter
			std::vector<double> lettersProbability(alphabet_.length(), 0.0);
			for (unsigned short i = 0; i < alphabet_.length(); i++) lettersProbability[i] = static_cast<double>(lettersCount[i]) / decrypted_message.length();

			// Calculate difference between statistics
			double currDif = 0;
			for (unsigned short i = 0; i < alphabet_.length(); i++) {
				// One statistic for letters Å ¨, so we have to count their probabilities together
				if (alphabet_[i] == 'Å') {
					currDif += (lettersProbability[i] + lettersProbability[i + 1] - lettersStatistics.find(alphabet_[i])->second) * (lettersProbability[i] + lettersProbability[i + 1] - lettersStatistics.find(alphabet_[i])->second);
					i += 1;
					continue;
				}
				// Same for letters Ú Ü
				else if (alphabet_[i] == 'Ú') {
					currDif += (lettersProbability[i] + lettersProbability[i + 2] - lettersStatistics.find(alphabet_[i])->second) * (lettersProbability[i] + lettersProbability[i + 2] - lettersStatistics.find(alphabet_[i])->second);
					continue;
				}
				// Just skip this letter cause we count it before
				else if (alphabet_[i] == 'Ü') { continue; }
				// Default case for all other letters
				else
					currDif += (lettersProbability[i] - lettersStatistics.find(alphabet_[i])->second) * (lettersProbability[i] - lettersStatistics.find(alphabet_[i])->second);
			}

			if (firstCalculate) {
				diffMin = currDif;
				keys.first = a;
				keys.second = b;
				firstCalculate = false;
			}
			else if (currDif < diffMin) {
				diffMin = currDif;
				keys.first = a;
				keys.second = b;
			}
		}
	}

	std::cout << "Best keys: a = " << keys.first << ", b = " << keys.second << std::endl;
}
