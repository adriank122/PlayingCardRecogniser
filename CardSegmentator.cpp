#include "CardSegmentator.h"


CardSegmentator::CardSegmentator()
{
}


CardSegmentator::~CardSegmentator()
{
}

	//initial function - initialise the process of class CardSegmentator
void CardSegmentator::init(Interface &interface) {
	preprocessInput(interface);
	findContoursOfCards(interface);
	separateCards(interface, contoursOfCards);
}

	//preprocessing function - blurring, converting to grayscale and global thresholding
void CardSegmentator::preprocessInput(Interface &interface) {
	Mat inputFiltered, inputGray, inputThreshold;

	medianBlur(interface.getInput(), inputFiltered, 5);
	cvtColor(inputFiltered, inputGray, COLOR_BGR2GRAY);
	threshold(inputGray, inputThreshold, 20, 255, THRESH_BINARY);

	interface.setInputFiltered(inputFiltered);
	interface.setInputGray(inputGray);
	interface.setInputThreshold(inputThreshold);
}

	//finding contours of cards in input using findContours() method 
	//with condition of area 10 000
	//and approximation the contours to 4 vertexes
void CardSegmentator::findContoursOfCards(Interface &interface) {
	Mat inputThreshold = interface.getInputThreshold();
	vector<vector<Point>> inputContours, inputContoursSelected;
	vector<Point> inputContoursPoint;
	findContours(inputThreshold, inputContours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	for (int i = 0; i < inputContours.size(); i++) {
		if (contourArea(inputContours[i]) > 10000) {
			approxPolyDP(inputContours[i], inputContoursPoint, 20, true);
			inputContoursSelected.push_back(inputContoursPoint);
		}
	}
	contoursOfCards = inputContoursSelected;
}

	//separating all cards from input 
	//and making perspective transformation to represent cards by rectangle
void CardSegmentator::separateCards(Interface &interface, vector<vector<Point>> &contoursOfCards) {
	vector<Mat> cards;
	for (int i = 0; i < contoursOfCards.size(); i++) {
		Mat card;
		vector<Point2f> srcPoints = { contoursOfCards[i][0], contoursOfCards[i][3], contoursOfCards[i][2], contoursOfCards[i][1] };
		vector<Point2f> dstPoints = { Point(0,0), Point(interface.getInput().cols - 1, 0), Point(interface.getInput().cols - 1, interface.getInput().rows - 1), Point(0,interface.getInput().rows - 1) };
		Mat T = getPerspectiveTransform(srcPoints, dstPoints);
		warpPerspective(interface.getInputFiltered(), card, T, interface.getInput().size());
		cards.push_back(card);
	}
	interface.setCards(cards);
}