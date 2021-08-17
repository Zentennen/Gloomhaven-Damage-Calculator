#include "Effect.h"
#include "Card.h"

Effect::Effect()
{
}

Effect::Effect(const Card& card)
{
    *this += card;
}

Effect& Effect::operator+=(const Card& other)
{   // mod
    damage += other.damage;
    if (other.stun) stun += 1.0f;
    if (other.disarm) disarm += 1.0f;
    if (other.immobilize) immobilize += 1.0f;
    if (other.muddle) muddle += 1.0f;
    if (other.poison) poison += 1.0f;
    if (other.wound) wound += 1.0f;
    if (other.curse) curse += 1.0f;
    if (other.heat) heat += 1.0f;
    if (other.frost) frost += 1.0f;
    if (other.earth) earth += 1.0f;
    if (other.air) air += 1.0f;
    if (other.night) night += 1.0f;
    if (other.light) light += 1.0f;
    return *this;
}

Effect& Effect::operator+=(const Effect& other)
{   // mod
    damage += other.damage;
    stun += other.stun;
    disarm += other.disarm;
    immobilize += other.immobilize;
    muddle += other.muddle;
    poison += other.poison;
    wound += other.wound;
    curse += other.curse;
    heat += other.heat;
    frost += other.frost;
    earth += other.earth;
    air += other.air;
    night += other.night;
    light += other.light;
    return *this;
}

Effect& Effect::operator/=(const size_t& denominator)
{   // mod
    damage /= denominator;
    stun /= denominator;
    disarm /= denominator;
    immobilize /= denominator;
    muddle /= denominator;
    poison /= denominator;
    wound /= denominator;
    curse /= denominator;
    heat /= denominator;
    frost /= denominator;
    earth /= denominator;
    air /= denominator;
    night /= denominator;
    light /= denominator;
    return *this;
}

std::string Effect::toString() const
{   // mod
    std::string str = "";
    str += std::to_string(damage) + " average damage modifier" + "\n";
    if (stun > 0.0) str += chanceTo(stun, "stun") + "\n";
    if (disarm > 0.0) str += chanceTo(disarm, "disarm") + "\n";
    if (immobilize > 0.0) str += chanceTo(immobilize, "immobilize") + "\n";
    if (muddle > 0.0) str += chanceTo(muddle, "muddle") + "\n";
    if (poison > 0.0) str += chanceTo(poison, "poison") + "\n";
    if (wound > 0.0) str += chanceTo(wound, "wound") + "\n";
    if (curse > 0.0) str += chanceTo(curse, "curse") + "\n";
    if (heat > 0.0) str += chanceTo(heat, "heat") + "\n";
    if (frost > 0.0) str += chanceTo(frost, "frost") + "\n";
    if (earth > 0.0) str += chanceTo(earth, "earth") + "\n";
    if (air > 0.0) str += chanceTo(air, "air") + "\n";
    if (night > 0.0) str += chanceTo(night, "night") + "\n";
    if (light > 0.0) str += chanceTo(light, "light") + "\n";
    return str;
}

Effect operator+(const Effect& eff, const Card& card)
{   // mod
    Effect ret = eff;
    ret.damage += card.damage;
    if (card.stun)         ret.stun += 1.0f;
    if (card.disarm)       ret.disarm += 1.0f;
    if (card.immobilize)   ret.immobilize += 1.0f;
    if (card.muddle)       ret.muddle += 1.0f;
    if (card.poison)       ret.poison += 1.0f;
    if (card.wound)        ret.wound += 1.0f;
    if (card.curse)        ret.curse += 1.0f;
    if (card.heat)         ret.heat += 1.0f;
    if (card.frost)        ret.frost += 1.0f;
    if (card.earth)        ret.earth += 1.0f;
    if (card.air)          ret.air += 1.0f;
    if (card.night)        ret.night += 1.0f;
    if (card.light)        ret.light += 1.0f;
    return ret;
}

Effect operator+(const Effect& a, const Effect& b)
{   // mod
    Effect ret;
    ret.damage      = a.damage + b.damage;
    ret.stun        = a.stun + b.stun;
    ret.disarm      = a.disarm + b.disarm;
    ret.immobilize  = a.immobilize + b.immobilize;
    ret.muddle      = a.muddle + b.muddle;
    ret.poison      = a.poison + b.poison;
    ret.wound       = a.wound + b.wound;
    ret.curse       = a.curse + b.curse;
    ret.heat        = a.heat + b.heat;
    ret.frost       = a.frost + b.frost;
    ret.earth       = a.earth + b.earth;
    ret.air         = a.air + b.air;
    ret.night       = a.night + b.night;
    ret.light       = a.light + b.light;
    return ret;
}

Effect operator/(const Effect& numerator, const size_t& denominator)
{   // mod
    Effect ret      = numerator;
    ret.damage      /= denominator;
    ret.stun        /= denominator;
    ret.disarm      /= denominator;
    ret.immobilize  /= denominator;
    ret.muddle      /= denominator;
    ret.poison      /= denominator;
    ret.wound       /= denominator;
    ret.curse       /= denominator;
    ret.heat        /= denominator;
    ret.frost       /= denominator;
    ret.earth       /= denominator;
    ret.air         /= denominator;
    ret.night       /= denominator;
    ret.light       /= denominator;
    return ret;
}
