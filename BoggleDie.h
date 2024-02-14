#pragma once

#include <string>

class BoggleDie {
public:
	BoggleDie();
	BoggleDie(std::string letter);
	void setLetter(std::string letter);
	void setIsTraversed(bool b);
	bool getIsTraversed();
	std::string getLetter();
private:
	bool isTraversed;
	std::string letter;
};
