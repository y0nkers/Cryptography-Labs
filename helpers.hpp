#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <utility>
#include <bitset>
#include <boost/dynamic_bitset.hpp>

std::string getStringFromFile(std::string filename);
bool isUnique(std::string str);
bool isInAlphabet(char& c, std::string alphabet);
bool isPrime(unsigned long long n);
bool isPowerOfTwo(unsigned long long n);
int gcd(int a, int b);

#endif // !HELPERS_HPP
