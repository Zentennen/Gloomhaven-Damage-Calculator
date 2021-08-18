#include "Core.h"

bool isADigit(const char& ch) {
    return ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9';
}

bool isADigitOrMinus(const char& ch) {
    return isADigit(ch) || ch == '-';
}

bool isAnInteger(const std::string& str) {
    FOR(str.length()) {
        if (!isADigit(str[i])) return false;
    }
    return true;
}

std::vector<std::string> separateByToken(const std::string& s, const char t)
{
    std::vector<std::string> ret;
    ret.reserve(20);
    size_t pos = s.find_first_not_of(t);
    size_t pos2 = s.find_first_of(t, pos);
    size_t count = pos2 - pos;
    while (pos != std::string::npos) {
        ret.push_back(s.substr(pos, count));
        pos = s.find_first_not_of(t, pos2);
        pos2 = s.find_first_of(t, pos);
        count = pos2 - pos;
    }
    return ret;
}

std::string chanceTo(const double& chance, std::string effect) {
    return std::to_string(chance * 100.0f) + "% chance to " + effect;
}