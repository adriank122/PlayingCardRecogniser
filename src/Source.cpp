/*
Adrian Kaliciecki
Playing Cards Recogniser

Application to recognition playing cards from 2 to 10.
The second function is calculation the geometric mean from all cards in photo.
*/

#include "Interface.h"
#include "CardSegmentator.h"
#include "SymbolSegmentator.h"
#include "SymbolClassifier.h"
#include "ResultGetter.h"

using namespace std;
using namespace cv;

int main() {

	Interface interface;
	CardSegmentator cardSegmentator;
	SymbolSegmentator symbolSegmentator;
	SymbolClassifier symbolClassifier;
	ResultGetter resultGetter;

	interface.init();
	cardSegmentator.init(interface);
	symbolSegmentator.init(interface);
	symbolClassifier.init(interface, symbolSegmentator);
	resultGetter.init(interface, symbolSegmentator, symbolClassifier);

	namedWindow("Card Recogniser", WINDOW_NORMAL);
	imshow("Card Recogniser", interface.getOutput());
	waitKey(0);
	return 0;
}