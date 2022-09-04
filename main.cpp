#include "CaesarWithKeyword.hpp"
#include "SimpleEncryptionTables.hpp"
#include "Vigenere.hpp"

int main(int argv, char** argc) {
	std::cout << "What method do you want to use?\n1 - Caesar cipher with keyword.\n2 - Simple encryption tables method.\n3 - Vigenere Cipher.\n";
	int choice = 0;
	do {
		std::cout << "Your choice: ";
		std::cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3);

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
	}

	return 0;
}
