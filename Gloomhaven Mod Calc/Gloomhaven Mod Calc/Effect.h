#pragma once
#include "Card.h"

struct Effect
{
    double damage = 0.0f;
    double stun = 0.0f;
    double disarm = 0.0f;
    double immobilize = 0.0f;
    double muddle = 0.0f;
    double poison = 0.0f;
    double wound = 0.0f;
    double curse = 0.0f;
    double heat = 0.0f;
    double frost = 0.0f;
    double earth = 0.0f;
    double air = 0.0f;
    double night = 0.0f;
    double light = 0.0f;
    Effect();
    Effect(const Card& card);
    friend Effect operator+(const Effect& eff, const Card& card);
    Effect& operator+=(const Card& other);
    friend Effect operator+(const Effect& a, const Effect& b);
    Effect& operator+=(const Effect& other);
    friend Effect operator/(const Effect& numerator, const size_t& denominator);
    Effect& operator/=(const size_t& denominator);
    std::string toString() const;
};