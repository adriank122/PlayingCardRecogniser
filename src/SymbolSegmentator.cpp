#include "SymbolSegmentator.h"



SymbolSegmentator::SymbolSegmentator()
{
}


SymbolSegmentator::~SymbolSegmentator()
{
}

	//initial function - initialise the process of class SymbolSegmentator
void SymbolSegmentator::init(Interface &interface) {
	preprocessCard(interface);
	separateSymbolsRoi(interface);
	findContoursOfSymbols(interface);
	countCardsWithFoundedContoursOfSymbols();
		//when input is in very bad quality (blurred case) change the way of processing
	if (counterOfCardsWithFoundedContoursOfSymbols == 0) {
		findcontoursOfSymbolsForSpecialCase(interface);
	}
	separateSymbols(interface);
}

	//preprocessing function - for all cards making convertion to grayscale, adaptive threshold and morphological erosion
void SymbolSegmentator::preprocessCard(Interface &interface) {
	vector<Mat> cards = interface.getCards();
	vector<Mat> cardsGray, cardsThreshold, cardsErode;
	for (int i = 0; i < cards.size(); i++) {
		Mat cardGray, cardThreshold, cardErode;
		Mat kernel = Mat::ones(Size(3, 3), CV_8U);
		cvtColor(cards[i], cardGray, COLOR_BGR2GRAY);
		adaptiveThreshold(cardGray, cardThreshold, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 2);
		morphologyEx(cardThreshold, cardErode, MORPH_ERODE, kernel, Point(), 9);

		cardsGray.push_back(cardGray);
		cardsThreshold.push_back(cardThreshold);
		cardsErode.push_back(cardErode);
	}
	interface.setCardsGray(cardsGray);
	interface.setCardsThreshold(cardsThreshold);
	interface.setCardsErode(cardsErode);
}

	//separating the region of cards where only a symbols are
	//region is set as a constant for all cases rectangle 
void SymbolSegmentator::separateSymbolsRoi(Interface &interface) {
	vector<Mat> cardsErode = interface.getCardsErode();
	vector<Mat> cardsErodeRoi;
	for (int i = 0; i < cardsErode.size(); i++) {
		Mat cardErodeRoi = Mat::ones(cardsErode[i].size(), CV_8UC1) * 255;
		Rect roi = Rect(400, 0, cardsErode[i].cols - 2 * 400, cardsErode[i].rows);
		cardsErode[i](roi).copyTo(cardErodeRoi(roi));
		cardsErodeRoi.push_back(cardErodeRoi);
	}
	interface.setSymbolsRoi(cardsErodeRoi);
}
	//finding contours of symbols in each card using findContours() method 
	//with condition of area between 24 000 and 100 000
void SymbolSegmentator::findContoursOfSymbols(Interface &interface) {
	vector<Mat> symbolsRoi = interface.getSymbolsRoi();
	for (int i = 0; i < symbolsRoi.size(); i++) {
		vector<vector<Point>> cardContours, cardContoursSelected;
		findContours(symbolsRoi[i], cardContours, RETR_TREE, CHAIN_APPROX_SIMPLE);
		for (int i = 0; i < cardContours.size(); i++) {
			if (contourArea(cardContours[i]) > 24000 && contourArea(cardContours[i]) < 100000) {
				cardContoursSelected.push_back(cardContours[i]);
			}
		}
		symbolsContours.push_back(cardContoursSelected);
	}
}

	//checking whether the contours have been found or not
	//if not - input is in very bad quality (blurred case)
void SymbolSegmentator::countCardsWithFoundedContoursOfSymbols() {
	counterOfCardsWithFoundedContoursOfSymbols = 0;
	for (int i = 0; i < symbolsContours.size(); i++) {
		if (symbolsContours[i].size() > 0) {
			counterOfCardsWithFoundedContoursOfSymbols++;
		}
	}
}

	//different way to process cards
	//use only when input is in very bad quality (blurred case)
	//it contains - global thresholding, setting symbols roi, contours finding with condition of area between 9 000 and 100 000
void SymbolSegmentator::findcontoursOfSymbolsForSpecialCase(Interface &interface) {
	symbolsContours.clear();
	vector<Mat> cardsGray = interface.getCardsGray();
	vector<Mat> cardsThreshold, cardsThresholdRoi;
	for (int i = 0; i < cardsGray.size(); i++) {
		Mat cardThreshold;
		threshold(cardsGray[i], cardThreshold, 132, 255, THRESH_BINARY);
		Mat cardThresholdRoi = Mat::ones(cardsGray[i].size(), CV_8UC1) * 255;
		Rect roi = Rect(400, 0, cardsGray[i].cols - 2 * 400, cardsGray[i].rows);
		cardThreshold(roi).copyTo(cardThresholdRoi(roi));

		vector<vector<Point>> cardContours, cardContoursSelected;
		findContours(cardThresholdRoi, cardContours, RETR_TREE, CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < cardContours.size(); i++) {
			if (contourArea(cardContours[i]) > 9000 && contourArea(cardContours[i]) < 100000) {
				cardContoursSelected.push_back(cardContours[i]);
			}
		}
		symbolsContours.push_back(cardContoursSelected);
		cardsThreshold.push_back(cardThreshold);
		cardsThresholdRoi.push_back(cardThresholdRoi);
	}
	interface.setCardsThreshold(cardsThreshold);
	interface.setSymbolsRoi(cardsThresholdRoi);
	interface.clearCardsErode();
}

	//separating only one symbol from each card
	//by selecting the last element from vector of symbols
	//and bounding it by a rectangle
void SymbolSegmentator::separateSymbols(Interface &interface) {
	vector<Mat> symbolsRoi = interface.getSymbolsRoi();
	vector<Mat> symbols;
	for (int i = 0; i < symbolsRoi.size(); i++) {
		Mat symbol;
		Rect symbolRoi = boundingRect(symbolsContours[i][symbolsContours[i].size()-1]);
		symbolsRoi[i](symbolRoi).copyTo(symbol);
		symbols.push_back(symbol);
	}
	interface.setSymbols(symbols);
}

	//getters of private fields of class SymbolSegmentator
vector<vector<vector<Point>>> SymbolSegmentator::getSymbolsContours() {
	return symbolsContours;
}

int SymbolSegmentator::getCounterOfCardsWithFoundedContoursOfSymbols() {
	return counterOfCardsWithFoundedContoursOfSymbols;
}