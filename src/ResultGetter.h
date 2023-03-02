#pragma once

#include "Interface.h"
#include "SymbolSegmentator.h"
#include "SymbolClassifier.h"

#include <cmath>

class ResultGetter
{
private:
	vector<int> numbersOfCards;
	vector<int> symbolsOfCards;				//1 - Hearts, 2 - Diamonds, 3 - Spades, 4 - Clubs
	double geometricMeanOfCardsNumbers;
public:
	ResultGetter();
	~ResultGetter();

	void init(Interface &interface, SymbolSegmentator &symbolSegmentator, SymbolClassifier &symbolClassifier);
	void getNumbersOfCards(SymbolSegmentator &symbolSegmentator);
	void getSymbolsOfCards(SymbolClassifier &symbolClassifier);
	void calculateGeometricMeanOfCardNumbers();
	void showResults(Interface &interface);
};

