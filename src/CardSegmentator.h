#pragma once

#include "Interface.h"

class CardSegmentator
{
private:
	vector<vector<Point>> contoursOfCards;
public:
	CardSegmentator();
	~CardSegmentator();

	void init(Interface &interface);
	void preprocessInput(Interface &interface);
	void findContoursOfCards(Interface &interface);
	void separateCards(Interface &interface, vector<vector<Point>> &contoursOfCards);
};