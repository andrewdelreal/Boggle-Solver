#include "BoggleBoard.h"

#include <ctime>

int main(int argc, char * agrv[]) {
	srand(time(0));
	// enter file path to dictionary txt file
	BoggleBoard bb("C:\\Users\\PC\\source\\repos\\Data Structures\\Projects\\Project4\\BigDictionary.txt");

	bb.printBoard(); 
	std::cout << "Show Solutions? (Y/N)\n";
	std::string response = "";
	std::cin >> response;
	while (response != "Y") {
		if (response == "N") {
			break;
		}
		std::cout << "Invalid Response\n";
		std::cin >> response;
	}
	if (response == "Y") {
		bb.solve();
	}
	
	return 0;
}
