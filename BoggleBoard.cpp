#include "BoggleBoard.h"

#include <cmath>

BoggleBoard::BoggleBoard(const std::string& pathToDictionary)
	: words(pathToDictionary), BOARD_DIMENSION(sqrt(NUM_OF_DIE))
{
	
	allDice.resize(NUM_OF_DIE);
	
	for (int i = 0; i < NUM_OF_DIE; i++) {
		BoggleDie* temp = new BoggleDie(faces[i][rand() % 6]);
		allDice.at(i) = temp;
	}
	shuffleBoard();
	board.resize(BOARD_DIMENSION);
	for (size_t i = 0; i < BOARD_DIMENSION; i++) {
		board.at(i).resize(BOARD_DIMENSION);
	}
	for (int i = 0; i < NUM_OF_DIE; i++) {
		board.at(i % BOARD_DIMENSION).at(i / BOARD_DIMENSION) = allDice.at(i);
	}
	
	/*
	allDice.at(0) = new BoggleDie("E");
	allDice.at(1) = new BoggleDie("N");
	allDice.at(2) = new BoggleDie("R");
	allDice.at(3) = new BoggleDie("O");
	allDice.at(4) = new BoggleDie("O");
	allDice.at(5) = new BoggleDie("A");
	allDice.at(6) = new BoggleDie("Qu");
	allDice.at(7) = new BoggleDie("K");
	allDice.at(8) = new BoggleDie("U");
	allDice.at(9) = new BoggleDie("N");
	allDice.at(10) = new BoggleDie("E");
	allDice.at(11) = new BoggleDie("T");
	allDice.at(12) = new BoggleDie("T");
	allDice.at(13) = new BoggleDie("R");
	allDice.at(14) = new BoggleDie("S");
	allDice.at(15) = new BoggleDie("L");
	allDice.at(16) = new BoggleDie("D");
	allDice.at(17) = new BoggleDie("T");
	allDice.at(18) = new BoggleDie("G");
	allDice.at(19) = new BoggleDie("S");
	allDice.at(20) = new BoggleDie("Y");
	allDice.at(21) = new BoggleDie("G");
	allDice.at(22) = new BoggleDie("O");
	allDice.at(23) = new BoggleDie("A");
	allDice.at(24) = new BoggleDie("N");

	board.resize(BOARD_DIMENSION);
	for (size_t i = 0; i < BOARD_DIMENSION; i++) {
		board.at(i).resize(BOARD_DIMENSION);
	}

	for (int i = 0; i < NUM_OF_DIE; i++) {
		board.at(i % BOARD_DIMENSION).at(i / BOARD_DIMENSION) = allDice.at(i);
	}
	*/
}

BoggleBoard::~BoggleBoard() {
	for (size_t i = 0; i < NUM_OF_DIE; i++) {
		//std::cout << "\tDeleting Die " << allDice.at(i)->getLetter() << std::endl;
		delete allDice.at(i);
		allDice.at(i) = NULL;
	}
}

void BoggleBoard::printBoard() {
	for (int i = 0; i < NUM_OF_DIE; i++) {
		if (board.at(i % BOARD_DIMENSION).at(i / BOARD_DIMENSION)->getLetter().size() == 1) {
			std::cout << board.at(i % BOARD_DIMENSION).at(i / BOARD_DIMENSION)->getLetter() << "  ";
		}
		else {
			std::cout << board.at(i % BOARD_DIMENSION).at(i / BOARD_DIMENSION)->getLetter() << " ";
		}
		if (i > 0 && ((i + 1) % BOARD_DIMENSION) == 0) {
			std::cout << std::endl;
		}
	}
}
void BoggleBoard::solve() {
	for (int i = 0; i < NUM_OF_DIE; i++) {
		solveHelper("", (i % 5), (i / 5));
	}
	
	std::vector<std::string> temp(foundWords.size());
	int k = 0;
	for (auto s : foundWords) {
		temp[k] = s;
		k++;
	}
	bubbleSort(temp);

	std::cout << "All possible values from longest to shortest\n";

	size_t currentSize = temp.back().size();

	std::cout << "Length: " << currentSize << " words\n";
	size_t tempSize = temp.size();
	for (size_t i = 0; i < tempSize; i++) {
		if (temp.back().size() < currentSize) {
			currentSize = temp.back().size();
			std::cout << "\nLength: " << currentSize << " words\n";
		}
		std::cout << temp.back() << " ";
		temp.pop_back();
	}
	std::cout << std::endl;
}

void BoggleBoard::bubbleSort(std::vector<std::string>& temp) {
	int n = temp.size();
	for (int i = 0; i < n - 1; i++){
		// Last i elements are already 
		// in place 
		for (int j = 0; j < n - i - 1; j++) {
			if (temp[j].size() > temp[j + 1].size()) {

				std::swap(temp[j], temp[j + 1]);
			}
		}
	}
}

void BoggleBoard::solveHelper(std::string word, int x, int y) {
	// coordinates in range
	if ((x >= 0 && x < BOARD_DIMENSION) && (y >= 0 && y < BOARD_DIMENSION)) {
		if (!board.at(x).at(y)->getIsTraversed()) {
			board.at(x).at(y)->setIsTraversed(true);

			std::string currentWord = word + board.at(x).at(y)->getLetter();
			std::string result = words.search(currentWord);
			if (currentWord == "STREET") {
				std::cout << "stop";
			}
			if (result == "FOUND") {
				if (currentWord.size() > 3) {
					foundWords.insert(currentWord);
				}
				checkDirections(currentWord, x, y);
			}
			else if (result == "PARTIAL") {
				checkDirections(currentWord, x, y);
			}
			else {
				// word not found
				
			}
			board.at(x).at(y)->setIsTraversed(false);

		}
	}
}

void BoggleBoard::checkDirections(std::string word, int x, int y) {
	solveHelper(word, x + 1, y);
	solveHelper(word, x - 1, y);
	solveHelper(word, x, y + 1);
	solveHelper(word, x, y - 1);
	solveHelper(word, x + 1, y - 1);
	solveHelper(word, x - 1, y + 1);
	solveHelper(word, x + 1, y + 1);
	solveHelper(word, x - 1, y - 1);
}

void BoggleBoard::shuffleBoard() {
	for (size_t i = 0; i < allDice.size(); i++) {
		size_t idx1 = (rand() % allDice.size());
		size_t idx2 = (rand() % allDice.size());
		BoggleDie* temp = allDice.at(idx1);
		allDice.at(idx1) = allDice.at(idx2);
		allDice.at(idx2) = temp;
	}
}
