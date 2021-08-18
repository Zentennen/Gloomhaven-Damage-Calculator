#pragma once
#include "Core.h"

struct Card {
    int damage = 0;
    bool rolling = false;
    bool stun = false;
    bool disarm = false;
    bool immobilize = false;
    bool muddle = false;
    bool poison = false;
    bool wound = false;
    bool curse = false;
    bool heat = false;
    bool frost = false;
    bool earth = false;
    bool air = false;
    bool night = false;
    bool light = false;
    Card();
    Card(const int& dmg);
    Card(const std::string& code);
    Card& operator+=(const Card& other);
    friend Card operator+(const Card& a, const Card& b);
    friend bool operator==(const Card& a, const Card& b);
    std::string toString() const;
    static Card max(const Card& a, const Card& b);
    static Card min(const Card& a, const Card& b);
};
