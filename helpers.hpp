#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <utility>

std::string getStringFromFile(std::string filename);
bool isUnique(std::string str);
bool isInAlphabet(char& c, std::string alphabet);
int gcd(int a, int b);

#endif // !HELPERS_HPP
