#pragma once
#include "Card.h"

#define CARD_UNIQUE_MOD_CHECK(x) if(a.x && !b.x) { if(bHasUniqueMod) return a; aHasUniqueMod = true; } else if(b.x && !a.x) { if(aHasUniqueMod) return a; bHasUniqueMod = true; }
#define CARD_CODE_CHAR_CHECK(small, capital, field) else if (code[i] == small || code[i] == capital) field = true

Card::Card()
{
}

Card::Card(const int& dmg)
	: damage(dmg)
{
}

Card::Card(const std::string& code)
{   // mod
    int damageStep = 0;
    std::string num;
    FOR(code.length()) {
        if (isADigitOrMinus(code[i]) && damageStep == 0) damageStep = 1;
        if (damageStep == 1) {
            if (isADigitOrMinus(code[i])) {
                num += code[i];
                continue;
            }
            else damageStep = 2;
        }
        if (code[i] == 'r' || code[i] == 'R') rolling = true;
        CARD_CODE_CHAR_CHECK('s', 'S', stun);
        CARD_CODE_CHAR_CHECK('d', 'D', disarm);
        CARD_CODE_CHAR_CHECK('i', 'I', immobilize);
        CARD_CODE_CHAR_CHECK('m', 'M', muddle);
        CARD_CODE_CHAR_CHECK('p', 'P', poison);
        CARD_CODE_CHAR_CHECK('w', 'W', wound);
        CARD_CODE_CHAR_CHECK('c', 'C', curse);
        CARD_CODE_CHAR_CHECK('h', 'H', heat);
        CARD_CODE_CHAR_CHECK('f', 'F', frost);
        CARD_CODE_CHAR_CHECK('e', 'E', earth);
        CARD_CODE_CHAR_CHECK('a', 'A', air);
        CARD_CODE_CHAR_CHECK('n', 'N', night);
        CARD_CODE_CHAR_CHECK('l', 'L', light);
    }
    if (num.length() > 0) damage = std::stoi(num);
}

Card& Card::operator+=(const Card& other)
{   // mod
    damage += other.damage;
    rolling = rolling && other.rolling;
    stun = stun || other.stun;
    disarm = disarm || other.disarm;
    immobilize = immobilize || other.immobilize;
    muddle = muddle || other.muddle;
    poison = poison || other.poison;
    wound = wound || other.wound;
    curse = curse || other.curse;
    heat = heat || other.heat;
    frost = frost || other.frost;
    earth = earth || other.earth;
    air = air || other.air;
    night = night || other.night;
    light = light || other.light;
    return *this;
}

std::string Card::toString() const
{   // mod
    std::string str = "";
    if(damage != 0) str += std::to_string(damage);
    if (rolling) str += "R";
    if (stun) str += "S";
    if (disarm) str += "D";
    if (immobilize) str += "I";
    if (muddle) str += "M";
    if (poison) str += "P";
    if (wound) str += "W";
    if (curse) str += "C";
    if (heat) str += "H";
    if (frost) str += "F";
    if (earth) str += "E";
    if (air)str += "A";
    if (night) str += "N";
    if (light) str += "L";
    if (str == "") str = "0";
    return str;
}

Card Card::max(const Card& a, const Card& b)
{   // mod
    bool aHasUniqueMod = false;
    bool bHasUniqueMod = false;
    CARD_UNIQUE_MOD_CHECK(stun);
    CARD_UNIQUE_MOD_CHECK(disarm);
    CARD_UNIQUE_MOD_CHECK(immobilize);
    CARD_UNIQUE_MOD_CHECK(muddle);
    CARD_UNIQUE_MOD_CHECK(poison);
    CARD_UNIQUE_MOD_CHECK(wound);
    CARD_UNIQUE_MOD_CHECK(curse);
    CARD_UNIQUE_MOD_CHECK(heat);
    CARD_UNIQUE_MOD_CHECK(frost);
    CARD_UNIQUE_MOD_CHECK(earth);
    CARD_UNIQUE_MOD_CHECK(air);
    CARD_UNIQUE_MOD_CHECK(night);
    CARD_UNIQUE_MOD_CHECK(light);
    if (aHasUniqueMod) return a;
    else if (bHasUniqueMod) {
        if (a.damage > b.damage) return a;
        else return b;
    }
    else if (b.damage > a.damage) return b;
    else return a;
}

Card Card::min(const Card& a, const Card& b)
{   // mod
    bool aHasUniqueMod = false;
    bool bHasUniqueMod = false;
    CARD_UNIQUE_MOD_CHECK(stun);
    CARD_UNIQUE_MOD_CHECK(disarm);
    CARD_UNIQUE_MOD_CHECK(immobilize);
    CARD_UNIQUE_MOD_CHECK(muddle);
    CARD_UNIQUE_MOD_CHECK(poison);
    CARD_UNIQUE_MOD_CHECK(wound);
    CARD_UNIQUE_MOD_CHECK(curse);
    CARD_UNIQUE_MOD_CHECK(heat);
    CARD_UNIQUE_MOD_CHECK(frost);
    CARD_UNIQUE_MOD_CHECK(earth);
    CARD_UNIQUE_MOD_CHECK(air);
    CARD_UNIQUE_MOD_CHECK(night);
    CARD_UNIQUE_MOD_CHECK(light);
    if (aHasUniqueMod) {
        if (a.damage < b.damage) return a;
        else return b;
    }
    else if (bHasUniqueMod) return a;
    else if (b.damage < a.damage) return b;
    else return a;
}

Card operator+(const Card& a, const Card& b)
{   // mod
    Card result;
    result.damage = a.damage + b.damage;
    result.rolling = a.rolling && b.rolling;
    result.stun = a.stun || b.stun;
    result.disarm = a.disarm || b.disarm;
    result.immobilize = a.immobilize || b.immobilize;
    result.muddle = a.muddle || b.muddle;
    result.poison = a.poison || b.poison;
    result.wound = a.wound || b.wound;
    result.curse = a.curse || b.curse;
    result.heat = a.heat || b.heat;
    result.frost = a.frost || b.frost;
    result.earth = a.earth || b.earth;
    result.air = a.air || b.air;
    result.night = a.night || b.night;
    result.light = a.light || b.light;
    return result;
}

bool operator==(const Card& a, const Card& b)
{   // mod
    return a.damage == b.damage &&
        a.rolling == b.rolling &&
        a.stun == b.stun &&
        a.disarm == b.disarm &&
        a.immobilize == b.immobilize &&
        a.muddle == b.muddle &&
        a.poison == b.poison &&
        a.wound == b.wound &&
        a.curse == b.curse &&
        a.heat == b.heat &&
        a.frost == b.frost &&
        a.earth == b.earth &&
        a.air == b.air &&
        a.night == b.night &&
        a.light == b.light;
}
