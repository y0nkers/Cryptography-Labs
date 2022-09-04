#include "CaesarWithKeyword.hpp"
#include "SimpleEncryptionTables.hpp"

int main(int argv, char** argc) {
	std::string message_string = getStringFromFile("message.txt");

	std::cout << "What method do you want to use?\n1 - Caesar cipher with keyword.\n2 - Simple encryption tables method.\n";
	int choice = 0;
	do {
		std::cout << "Your choice: ";
		std::cin >> choice;
	} while (choice != 1 && choice != 2);

	switch (choice) {
	case 1:
		{
			unsigned short digit_key = 0;
			CaesarWithKeyword caesar("alphabet.txt", "keyword.txt", digit_key);

			do {
				std::cout << "Enter a digit key (0 <= K <= " << caesar.getAlphabet().length() - 1 << "): ";
				std::cin >> digit_key;
			} while ((digit_key < 0) || (digit_key > caesar.getAlphabet().length() - 1));

			caesar.setDigitKey(digit_key);
			caesar.convertAlphabet();
			caesar.encrypt(message_string, "encrypted.txt");
			caesar.decrypt("encrypted.txt", "decrypted.txt");
		}
		break;
	case 2:
		{
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
			tables.encrypt(message_string, "encrypted.txt");
			tables.decrypt("encrypted.txt", "decrypted.txt");
		}
		break;
	}

	return 0;
}