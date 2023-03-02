#include "ResultGetter.h"


ResultGetter::ResultGetter()
{
}


ResultGetter::~ResultGetter()
{
}

	//initial function - initialise the process of class ResultGetter
void ResultGetter::init(Interface &interface, SymbolSegmentator &symbolSegmentator, SymbolClassifier &symbolClassifier) {
	getNumbersOfCards(symbolSegmentator);
	getSymbolsOfCards(symbolClassifier);
	calculateGeometricMeanOfCardNumbers();
	showResults(interface);
}

	//getting numbers of all cards
void ResultGetter::getNumbersOfCards(SymbolSegmentator &symbolSegmentator) {
	vector<vector<vector<Point>>> symbolsContours = symbolSegmentator.getSymbolsContours();
	for (int i = 0; i < symbolsContours.size(); i++) {
		numbersOfCards.push_back(symbolsContours[i].size());
	}
}

	//getting symbols of all cards
void ResultGetter::getSymbolsOfCards(SymbolClassifier &symbolClassifier) {
	symbolsOfCards = symbolClassifier.getSymbolsOfCards();
}

	//calcualting geometric mean of all card numbers
void ResultGetter::calculateGeometricMeanOfCardNumbers() {
	double a = 1;
	double n = numbersOfCards.size();
	for (int i = 0; i < numbersOfCards.size(); i++) {
		a *= numbersOfCards[i];
	}
	geometricMeanOfCardsNumbers = pow(a, 1.0 / n);
}

	//showing results as information about what cards are recognised 
	//and value of geometric mean
void ResultGetter::showResults(Interface &interface) {
	Mat output = interface.getOutput();
	string cardsInfo = "There are: ";
	for (int i = numbersOfCards.size() -1; i >= 0; i--) {
		cardsInfo += to_string(numbersOfCards[i]) + " ";
		if (symbolsOfCards[i] == 1) {
			cardsInfo += "Hearts, ";
		}
		if (symbolsOfCards[i] == 2) {
			cardsInfo += "Diamonds, ";
		}
		if (symbolsOfCards[i] == 3) {
			cardsInfo += "Spades, ";
		}
		if (symbolsOfCards[i] == 4) {
			cardsInfo += "Clubs, ";
		}
	}
	string geometricMeanInfo = "Geometric mean of all cards is : " + to_string(geometricMeanOfCardsNumbers);
	putText(output, cardsInfo, Point(100, 1300), FONT_HERSHEY_DUPLEX, 1.8, Scalar(0, 0, 255), 2, 8);
	putText(output, geometricMeanInfo, Point(100, 1400), FONT_HERSHEY_DUPLEX, 1.8, Scalar(0, 0, 255), 2, 8);
}