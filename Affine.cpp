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

void Affine::cryptoanalysis(std::string encrypted_filename) {
	// Letter probability distribution statistics in Russian texts
	// 1 prorability for letters Å ¨ and 1 for Ü Ú
	std::unordered_map<char, double> lettersStatistics = {
		{'À', 0.062},
		{'Á', 0.014},
		{'Â', 0.038},
		{'Ã', 0.013},
		{'Ä', 0.025},
		{'Å', 0.072},
		{'¨', 0.072},
		{'Æ', 0.007},
		{'Ç', 0.016},
		{'È', 0.062},
		{'É', 0.010},
		{'Ê', 0.028},
		{'Ë', 0.035},
		{'Ì', 0.026},
		{'Í', 0.053},
		{'Î', 0.090},
		{'Ï', 0.023},
		{'Ð', 0.040},
		{'Ñ', 0.045},
		{'Ò', 0.053},
		{'Ó', 0.021},
		{'Ô', 0.002},
		{'Õ', 0.009},
		{'Ö', 0.004},
		{'×', 0.012},
		{'Ø', 0.006},
		{'Ù', 0.003},
		{'Ú', 0.014},
		{'Û', 0.016},
		{'Ü', 0.014},
		{'Ý', 0.003},
		{'Þ', 0.006},
		{'ß', 0.018},
		{' ', 0.175}
	};

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

			std::string fragment(15, '0');
			for (int i = 0; i < 15; i++) fragment[i] = decrypted_message[i];
			std::cout << "a = " << a << ", b = " << b << ", W = " << currDif << ", " << fragment << std::endl;

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
