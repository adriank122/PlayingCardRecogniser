#pragma once

#include "Interface.h"
#include "SymbolSegmentator.h"

class SymbolClassifier
{
private:
	vector<vector<Rect>> partsOfSymbols;
	vector<vector<double>> percentOfSymbolsInParts;
	vector<int> symbolsOfCards;				//1 - Hearts, 2 - Diamonds, 3 - Spades, 4 - Clubs
public:
	SymbolClassifier();
	~SymbolClassifier();

	void init(Interface &interface, SymbolSegmentator &symbolSegmentator);
	void createPartsOfSymbols(Interface &interface);
	void calculatePercentOfSymbolsInParts(Interface &interface);
	void recogniseSymbols(Interface &interface, SymbolSegmentator &symbolSegmentator);
	vector<int> getSymbolsOfCards();
};

