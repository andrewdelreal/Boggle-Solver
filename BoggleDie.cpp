#include "BoggleDie.h"

BoggleDie::BoggleDie() {
	setLetter("");
	setIsTraversed(false);
}

BoggleDie::BoggleDie(std::string letter) {
	setLetter(letter);
	setIsTraversed(false);
}

void BoggleDie::setLetter(std::string letter) {
	this->letter = letter;
}

void BoggleDie::setIsTraversed(bool b) {
	isTraversed = b;
}

bool BoggleDie::getIsTraversed() {
	return isTraversed;
}

std::string BoggleDie::getLetter() {
	return letter;
}
