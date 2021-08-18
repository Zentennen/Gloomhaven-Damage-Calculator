#include "Deck.h"
#include <iostream>
#include <future>
#include <map>

#define fu std::future

Effect Deck::addRollingAvg(const Card& card, const std::vector<bool>& usedCards, size_t numAvailable) const
{
    Effect ret;
    FOR(cards.size()) {
        if (usedCards[i]) continue;
        Card c = cards[i] + card;
        if (c.rolling && numAvailable > 1) {
            auto uc = usedCards;
            uc[i] = true;
            ret += addRollingAvg(c, uc, numAvailable - 1) / (numAvailable - 1);
        }
        else {
            ret += c;
        }
    }
    return ret;
}

Effect Deck::addRollingAvgDis(const std::vector<bool>& usedCards, size_t numAvailable) const
{
    Effect ret;
    FOR(cards.size()) {
        if (usedCards[i]) continue;
        if (cards[i].rolling && numAvailable > 1) {
            auto uc = usedCards;
            uc[i] = true;
            addRollingAvgDis(uc, numAvailable - 1) / (numAvailable - 1);
        }
        else {
            ret += cards[i];
        }
    }
    return ret;
}

Effect Deck::averageNeu(size_t i) const
{
    Effect result;
    size_t deckSize = cards.size();
    size_t deckSize_1 = deckSize - 1;
    const Card& a = cards[i];
    if (a.rolling && deckSize > 1) {
        std::vector<bool> usedCards;
        usedCards.resize(deckSize, false);
        usedCards[i] = true;
        result += addRollingAvg(a, usedCards, deckSize_1) / deckSize_1;
    }
    else {
        result += a;
    }
    return result;
}

Effect Deck::averageAdv(size_t i) const
{
    Effect result;
    size_t deckSize = cards.size();
    size_t deckSize_2 = deckSize - 2;
    const Card& a = cards[i];
    for (unsigned int j = 0; j < deckSize; j++) {
        if (i == j) continue;
        const Card& b = cards[j];
        if ((a.rolling || b.rolling) && deckSize > 1) {
            std::vector<bool> usedCards;
            usedCards.resize(deckSize, false);
            usedCards[i] = true;
            usedCards[j] = true;
            Card sum = a + b;
            if (sum.rolling) {
                result += addRollingAvg(sum, usedCards, deckSize_2) / deckSize_2;
            }
            else result += sum;
        }
        else result += Card::max(a, b);
    }
    return result;
}

Effect Deck::averageDis(size_t i) const
{
    Effect result;
    size_t deckSize = cards.size();
    size_t deckSize_2 = deckSize - 2;
    const Card& a = cards[i];
    for (unsigned int j = 0; j < deckSize; j++) {
        if (i == j) continue;
        const Card& b = cards[j];
        if (a.rolling && b.rolling && deckSize > 1) {
            std::vector<bool> usedCards;
            usedCards.resize(deckSize, false);
            usedCards[i] = true;
            usedCards[j] = true;
            result += addRollingAvgDis(usedCards, deckSize_2) / deckSize_2;
        }
        else {
            result += Card::min(a, b);
        }
    }
    return result;
}

Deck::Deck()
{
    cards.reserve(30);
}

void Deck::average(Advantage adv) const
{
    size_t deckSize = cards.size();
    if (deckSize == 0) {
        std::cout << "No cards in deck\n";
        return;
    }
    else if (deckSize == 1 && adv != Advantage::Neutral) {
        std::cout << "Deck size must be > 1 if advantage is non-neutral\n";
        return;
    }
    size_t deckPerm2 = deckSize * (deckSize - 1);
    Effect result;
    size_t denominator;
    std::vector<fu<Effect>> effects;
    effects.resize(deckSize);
    if (adv == Advantage::Neutral) {
        FOR(deckSize) {
            effects[i] = std::async(&Deck::averageNeu, this, i);
        }
        denominator = deckSize;
    }
    else if (adv == Advantage::Advantage) {
        FOR(deckSize) {
            effects[i] = std::async(&Deck::averageAdv, this, i);
        }
        denominator = deckPerm2;
    }
    else if (adv == Advantage::Disadvantage) {
        FOR(deckSize) {
            effects[i] = std::async(&Deck::averageDis, this, i);
        }
        denominator = deckPerm2;
    }
    else {
        std::cout << "ERR: Advantage invvalid\n";
        return;
    }
    FOR(effects.size()) {
        if (effects[i].valid()) {
            result += effects[i].get();
        }
        else {
            std::cout << "WRN: Effect future #" << i << " is invalid\n";
        }
    }
    result /= denominator;
    std::cout << result.toString();

}

void Deck::add(const Card& card, size_t count)
{
    FOR(count) {
        if (cards.capacity() == cards.size()) {
            cards.reserve(30);
        }
        cards.push_back(card);
    }
}

bool Deck::remove(const Card& card, size_t count)
{
    if (count == 0) return true;
    for (auto it = cards.begin(); it != cards.end();) {
        if (*it == card) {
            it = cards.erase(it);
            if (--count == 0) return true;
        }
        else {
            ++it;
        }
    }
    return false;
}

void Deck::clear()
{
    cards.clear();
}

void Deck::print() const
{
    if (cards.size() == 0) {
        std::cout << "No cards in deck\n";
        return;
    }
    std::map<std::string, size_t> strings;
    FOR(cards.size()) {
        auto cardStr = cards[i].toString();
        bool found = false;
        for (auto&& s : strings) {
            if (cardStr == s.first) {
                s.second++;
                found = true;
                break;
            }
        }
        if (!found) {
            strings.emplace(cardStr, 1);
        }
    }
    for (auto&& s : strings) {
        if (s.second < 2) {
            std::cout << s.first << "\n";
        }
        else {
            std::cout << s.first << " x" << s.second << "\n";
        }
    }
}

void Deck::setToDefault()
{
    cards.clear();
    cards.push_back(Card(-3));
    cards.push_back(Card(-2));
    FOR(5) cards.push_back(Card(-1));
    FOR(6) cards.push_back(Card(0));
    FOR(5) cards.push_back(Card(1));
    cards.push_back(Card(2));
    cards.push_back(Card(3));
}

size_t Deck::size() const
{
    return cards.size();
}

const Card& Deck::operator[](const size_t& i) const
{
    return cards[i];
}
