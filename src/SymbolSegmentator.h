#pragma once

#include "Interface.h"

class SymbolSegmentator
{
private:
	vector<vector<vector<Point>>> symbolsContours;
	int counterOfCardsWithFoundedContoursOfSymbols;
public:
	SymbolSegmentator();
	~SymbolSegmentator();

	void init(Interface &interface);
	void preprocessCard(Interface &interface);
	void separateSymbolsRoi(Interface &interface);
	void findContoursOfSymbols(Interface &interface);
	void countCardsWithFoundedContoursOfSymbols();
	void findcontoursOfSymbolsForSpecialCase(Interface &interface);
	void separateSymbols(Interface &interface);

	vector<vector<vector<Point>>> getSymbolsContours();
	int getCounterOfCardsWithFoundedContoursOfSymbols();
};

