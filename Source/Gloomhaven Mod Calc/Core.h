#pragma once
#include <string>
#include <assert.h>
#include <vector>

#define FOR(x) for(size_t i = 0; i < x; i++)
#define NL std::cout << "\n"
#define CNL << "\n" <<

enum class Advantage {
    Neutral, Advantage, Disadvantage
};

bool isADigit(const char& ch);
bool isADigitOrMinus(const char& ch);
bool isAnInteger(const std::string& str);
std::vector<std::string> separateByToken(const std::string& s, const char t);
std::string chanceTo(const double& chance, std::string effect);