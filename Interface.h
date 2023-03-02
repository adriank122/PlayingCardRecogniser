#pragma once

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

class Interface
{
private:
	Mat input, inputFiltered, inputGray, inputThreshold, output;
	vector<Mat> cards, cardsGray, cardsThreshold, cardsErode;
	vector<Mat> symbolsRoi, symbols;
	string inputPath;
public:
	Interface();
	~Interface();

	string getInputPath();
	void loadInput(string inputPath);
	void init();
	void clearCardsErode();

	Mat getInput();
	void setInput(Mat input);
	Mat getOutput();
	void setOutput(Mat output);
	Mat getInputFiltered();
	void setInputFiltered(Mat inputFiltered);
	Mat getInputGray();
	void setInputGray(Mat inputFiltered);
	Mat getInputThreshold();
	void setInputThreshold(Mat inputThreshold);
	vector<Mat> getCards();
	void setCards(vector<Mat> cards);
	vector<Mat> getCardsGray();
	void setCardsGray(vector<Mat> cardsGray);
	vector<Mat> getCardsThreshold();
	void setCardsThreshold(vector<Mat> cardsThreshold);
	vector<Mat> getCardsErode();
	void setCardsErode(vector<Mat> cardsErode);
	vector<Mat> getSymbolsRoi();
	void setSymbolsRoi(vector<Mat> symbolsRoi);
	vector<Mat> getSymbols();
	void setSymbols(vector<Mat> symbols);
};

