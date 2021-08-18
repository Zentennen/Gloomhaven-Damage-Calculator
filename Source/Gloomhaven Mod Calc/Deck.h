#pragma once
#include "Effect.h"

class Deck
{
	std::vector<Card> cards;
	Effect addRollingAvg(const Card& card, const std::vector<bool>& usedCards, size_t numAvailable) const;
	Effect addRollingAvgDis(const std::vector<bool>& usedCards, size_t numAvailable) const;
	Effect averageNeu(size_t i) const;
	Effect averageAdv(size_t i) const;
	Effect averageDis(size_t i) const;
public:
	Deck();
	void add(const Card& card, size_t count = 1);
	bool remove(const Card& card, size_t count = 1);
	void average(Advantage adv) const;
	void clear();
	void print() const;
	void setToDefault();
	size_t size() const;
	const Card& operator[](const size_t& i) const;
};