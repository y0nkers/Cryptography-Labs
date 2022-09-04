#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

std::string getStringFromFile(std::string filename);
bool isUnique(std::string str);
bool isInAlphabet(char& c, std::string alphabet);

#endif // !HELPERS_HPP
