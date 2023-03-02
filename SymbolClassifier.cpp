#include "SymbolClassifier.h"



SymbolClassifier::SymbolClassifier()
{
}

SymbolClassifier::~SymbolClassifier()
{
}

//initial function - initialise the process of class SymbolClassifier
void SymbolClassifier::init(Interface &interface, SymbolSegmentator &symbolSegmentator) {
	createPartsOfSymbols(interface);
	calculatePercentOfSymbolsInParts(interface);
	recogniseSymbols(interface, symbolSegmentator);
}

	//dividing a symbol region to 16 parts (4x4) which has the same size
void SymbolClassifier::createPartsOfSymbols(Interface &interface) {
	vector<Mat> symbols = interface.getSymbols();
	for (int i = 0; i < symbols.size(); i++) {
		vector<Rect> partsOfSymbol;
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				Rect part = Rect(Point(symbols[i].cols / 4 * k, symbols[i].rows / 4 * j), Point(symbols[i].cols/4 * (k+1), symbols[i].rows/4 * (j+1)));
				partsOfSymbol.push_back(part);
			}
		}
		partsOfSymbols.push_back(partsOfSymbol);
	}
}

	//calculating content of symbol in percent in each part of symbol region
void SymbolClassifier::calculatePercentOfSymbolsInParts(Interface &interface) {
	vector<Mat> symbols = interface.getSymbols();
	for(int i = 0; i < symbols.size(); i++) {
		vector<double> percentOfSymbolInParts;
		for (int j = 0; j < 16; j++) {
			Mat symbol = symbols[i];
			double areaOfPart = symbols[i].cols / 4 * symbols[i].rows / 4;
			double percentOfSymbolInPart = (areaOfPart - (sum(symbols[i](partsOfSymbols[i][j]))[0] / 255)) / areaOfPart * 100;
			percentOfSymbolInParts.push_back(percentOfSymbolInPart);
		}
		percentOfSymbolsInParts.push_back(percentOfSymbolInParts);
	}
}

	//recognising symbols based on content of symbol in each part of symbol region and ratio of symbol region dimensions
	//value 1 is Hearts, 2 is Diamonds, 3 is Spades and 4 is Clubs
	//there are 2 cases - one for standard processing and the second for a special case (blurred images)
void SymbolClassifier::recogniseSymbols(Interface &interface, SymbolSegmentator &symbolSegmentator) {
	int counterOfCardsWithFoundedContoursOfSymbols = symbolSegmentator.getCounterOfCardsWithFoundedContoursOfSymbols();
	vector<Mat> symbols = interface.getSymbols();
	if (counterOfCardsWithFoundedContoursOfSymbols != 0) {
		for (int i = 0; i < symbols.size(); i++) {
			if (percentOfSymbolsInParts[i][0] > 40 && percentOfSymbolsInParts[i][3] > 40) {
				symbolsOfCards.push_back(1);
			}else
			if ((percentOfSymbolsInParts[i][1] + percentOfSymbolsInParts[i][2]) / 2 > 55 && percentOfSymbolsInParts[i][0] < 10 && percentOfSymbolsInParts[i][12] > 10) {		
				symbolsOfCards.push_back(4);
			}else
			if ((percentOfSymbolsInParts[i][0] + percentOfSymbolsInParts[i][3]) / 2 < 6 && (percentOfSymbolsInParts[i][12] + percentOfSymbolsInParts[i][15]) / 2 < 8) {			
				symbolsOfCards.push_back(2);
			}else
			if ((percentOfSymbolsInParts[i][1] + percentOfSymbolsInParts[i][2]) / 2 < 55) {
				symbolsOfCards.push_back(3);
			}
		}
	}else{
		for (int i = 0; i < symbols.size(); i++) {
			double dimensionRatio = double(symbols[i].cols) / symbols[i].rows;
			if (dimensionRatio < 1.5) {
				symbolsOfCards.push_back(2);
			}
			else if ((percentOfSymbolsInParts[i][0] + percentOfSymbolsInParts[i][3]) / 2 > 50) {
				symbolsOfCards.push_back(1);
			}
			else if ((percentOfSymbolsInParts[i][1] + percentOfSymbolsInParts[i][2]) / 2 > 70) {
				symbolsOfCards.push_back(4);
			}
			else {
				symbolsOfCards.push_back(3);
			}
		}
	}
}

//getter of private field of class SymbolSegmentator
vector<int> SymbolClassifier::getSymbolsOfCards() {
	return symbolsOfCards;
}