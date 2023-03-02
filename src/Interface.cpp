#include "Interface.h"


Interface::Interface()
{
}


Interface::~Interface()
{
}
	//get input path from user in the form nameOfFile.extension
string Interface::getInputPath() {
	string inputPath;
	cout << "Wprowadz sciezke do pliku wejsciowego:" << endl;
	getline(cin, inputPath);
	return inputPath;
}
	//load input from input path
void Interface::loadInput(string inputPath) {
	input = imread(inputPath);
	if(input.empty()){
		cout << "Blad odczytu pliku!" << endl;
	}
}

	//initial function - initialise the process of class Interface
void Interface::init() {
	inputPath = getInputPath();
	loadInput(inputPath);
	input.copyTo(output);
}

	//clear vector cardsErode
void Interface::clearCardsErode() {
	this->cardsErode.clear();
}

	//setters and getters of private fields of class Interface
Mat Interface::getInput() {
	return input;
}

void Interface::setInput(Mat input) {
	this->input = input;
}

Mat Interface::getOutput() {
	return output;
}
void Interface::setOutput(Mat output) {
	this->output = output;
}

Mat Interface::getInputFiltered() {
	return inputFiltered;
}

void Interface::setInputFiltered(Mat inputFiltered) {
	this->inputFiltered = inputFiltered;
}

Mat Interface::getInputGray() {
	return inputGray;
}

void Interface::setInputGray(Mat inputGray) {
	this->inputGray = inputGray;
}

Mat Interface::getInputThreshold() {
	return inputThreshold;
}

void Interface::setInputThreshold(Mat inputThreshold) {
	this->inputThreshold = inputThreshold;
}

vector<Mat> Interface::getCards() {
	return cards;
}

void Interface::setCards(vector<Mat> cards) {
	this->cards = cards;
}

vector<Mat> Interface::getCardsGray() {
	return cardsGray;
}

void Interface::setCardsGray(vector<Mat> cardsGray) {
	this->cardsGray = cardsGray;
}

vector<Mat> Interface::getCardsThreshold() {
	return cardsThreshold;
}

void Interface::setCardsThreshold(vector<Mat> cardsThreshold) {
	this->cardsThreshold = cardsThreshold;
}

vector<Mat> Interface::getCardsErode() {
	return cardsErode;
}

void Interface::setCardsErode(vector<Mat> cardsErode) {
	this->cardsErode = cardsErode;
}

vector<Mat> Interface::getSymbolsRoi() {
	return symbolsRoi;
}

void Interface::setSymbolsRoi(vector<Mat> symbolsRoi) {
	this->symbolsRoi = symbolsRoi;
}

vector<Mat> Interface::getSymbols() {
	return symbols;
}

void Interface::setSymbols(vector<Mat> symbols) {
	this->symbols = symbols;
}