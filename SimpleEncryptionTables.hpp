#ifndef TABLES_HPP
#define TABLES_HPP

#include "helpers.hpp"

class SimpleEncryptionTables {
private:
	unsigned short rows_ = 0;
	unsigned short columns_ = 0;

public:
	SimpleEncryptionTables(unsigned short rowsCount, unsigned short columnsCount);
	void encrypt(std::string message, std::string filename);
	void decrypt(std::string encrypted_filename, std::string decrypted_filename);

	unsigned short getRows() { return rows_; };
	unsigned short getColumns() { return columns_; };

	void setRows(unsigned short rows) { rows_ = rows; };
	void setColumns(unsigned short columns) { columns_ = columns; };
};

#endif // !TABLES_HPP
