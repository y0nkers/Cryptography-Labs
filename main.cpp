#include "CaesarWithKeyword.hpp"
#include "SimpleEncryptionTables.hpp"
#include "Vigenere.hpp"
#include "Affine.hpp"
#include "LFSR.hpp"

// Letter probability distribution statistics in Russian texts
// 1 prorability for letters Å ¨ and 1 for Ü Ú
std::unordered_map<char, double> LettersStatistics = {
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

int main(int argv, char** argc) {
	system("chcp 1251");
	std::cout << "What method do you want to use?\n1 - Caesar cipher with keyword.\n2 - Simple encryption tables method.\n3 - Vigenere Cipher.\n4 - Affine Cipher.\n5 - LFSR generator.\n";
	int choice = 0;
	do {
		std::cout << "Your choice: ";
		std::cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);

	switch (choice) {
	case 1:
		{
			std::string message_string = getStringFromFile("input\\message.txt");
			unsigned short digit_key = 0;
			CaesarWithKeyword caesar("input\\alphabet_caesar.txt", "input\\keyword_caesar.txt", digit_key);

			do {
				std::cout << "Enter a digit key (0 <= K <= " << caesar.getAlphabet().length() - 1 << "): ";
				std::cin >> digit_key;
			} while ((digit_key < 0) || (digit_key > caesar.getAlphabet().length() - 1));

			caesar.setDigitKey(digit_key);
			caesar.convertAlphabet();
			caesar.encrypt(message_string, "output\\encrypted_caesar.txt");
			caesar.decrypt("output\\encrypted_caesar.txt", "output\\decrypted_caesar.txt");
			std::cout << caesar.getAlphabet() << std::endl;
			std::cout << caesar.getConvertedAlpabet() << std::endl;
		}
		break;
	case 2:
		{
			std::string message_string = getStringFromFile("input\\message.txt");
			unsigned short rows = 0, columns = 0;
			
			do {
				std::cout << "Enter the number of rows: ";
				std::cin >> rows;
			} while (rows < 0);

			do {
				std::cout << "Enter the number of columns: ";
				std::cin >> columns;
			} while (columns < 0);

			SimpleEncryptionTables tables(rows, columns);
			tables.encrypt(message_string, "output\\encrypted_tables.txt");
			tables.decrypt("output\\encrypted_tables.txt", "output\\decrypted_tables.txt");
		}
		break;
	case 3:
		{
			std::string message_string = getStringFromFile("input\\message_vigenere.txt");

			Vigenere vigenere("input\\alphabet_vigenere.txt", "input\\keyword_vigenere.txt");
			vigenere.encrypt(message_string, "output\\encrypted_vigenere.txt");
			vigenere.decrypt("output\\encrypted_vigenere.txt", "output\\decrypted_vigenere.txt");
		}
	break;
	case 4:
		{
			std::string affine_alphabet = getStringFromFile("input\\alphabet_affine.txt");
			Affine affine(affine_alphabet);
			std::string message_string = getStringFromFile("input\\message_affine.txt");

			unsigned short a = 0, b = 0;
			bool badGCD = false;

			do {
				std::cout << "Enter the key A (0 <= K <= " << affine.getAlphabet().length() - 1 << "): ";
				std::cin >> a;
				if (gcd(a, affine.getAlphabet().length()) != 1) {
					std::cout << "The Greatest Common Divisor of the key A and the number of letters in the alphabet must be equal to one!" << std::endl;
					badGCD = true;
				}
				else badGCD = false;
			} while ((a < 0) || (a > affine.getAlphabet().length() - 1) || badGCD);

			do {
				std::cout << "Enter the key B (0 <= K <= " << affine.getAlphabet().length() - 1 << "): ";
				std::cin >> b;
			} while ((b < 0) || (b > affine.getAlphabet().length() - 1));

			affine.setA(a);
			affine.setB(b);
			affine.convertAlphabet();
			affine.encrypt(message_string, "output\\encrypted_affine.txt");
			affine.decrypt("output\\encrypted_affine.txt", "output\\decrypted_affine.txt");
			affine.cryptoanalysis("output\\encrypted_affine.txt", LettersStatistics);
		}
	break;
	case 5:
		LFSR lfsr("input\\key_lfsr.txt", "input\\relations_lfsr.txt");
		std::bitset<32> generated = lfsr.generate();
		std::cout << std::endl << "First stage generator (LFSR output)" << std::endl << generated << " (" << generated.to_ulong() << ")" << std::endl;
		//for (int i = generated.size() - 1; i >= 0; --i) std::cout << generated[i];
		//std::cout << std::endl;
	}
	return 0;
}
