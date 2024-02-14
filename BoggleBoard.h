#pragma once

#include "Trie.h"
#include "BoggleDie.h"

#include <vector>
#include <iostream>
#include <string>
#include <unordered_set>

const int NUM_OF_DIE = 25;

class BoggleBoard
{
public:
    BoggleBoard(const std::string& pathToDictionary);
    ~BoggleBoard();
    void printBoard();
    void solve();
private:
    Trie words;
    std::vector<BoggleDie*> allDice;
    std::vector<std::vector<BoggleDie*>> board;
    std::unordered_set<std::string> foundWords;
    void bubbleSort(std::vector<std::string>& temp);
    const int BOARD_DIMENSION;
    void shuffleBoard();
    void solveHelper(std::string word, int x, int y);
    void checkDirections(std::string word, int x, int y);

};

const std::string faces[25][6] = {
    { "N", "S", "C", "T", "E", "C" },
    { "A", "E", "A", "E", "E", "E" },
    { "H", "H", "L", "R", "O", "D" },
    { "O", "R", "W", "V", "G", "R" },
    { "S", "P", "R", "I", "Y", "Y" },
    { "S", "U", "E", "N", "S", "S" },
    { "M", "E", "A", "U", "E", "G" },
    { "S", "E", "P", "T", "I", "C" },
    { "D", "H", "H", "O", "W", "N" },
    { "L", "E", "P", "T", "I", "S" },
    { "S", "T", "L", "I", "E", "I" },
    { "A", "R", "S", "I", "Y", "F" },
    { "T", "E", "T", "I", "I", "I" },
    { "O", "T", "T", "T", "M", "E" },
    { "N", "M", "N", "E", "G", "A" },
    { "N", "N", "E", "N", "A", "D" },
    { "O", "U", "O", "T", "T", "O" },
    { "B", "Z", "J", "B", "X", "K" },
    { "A", "A", "F", "A", "S", "R" },
    { "T", "O", "O", "U", "W", "N" },
    { "O", "T", "H", "D", "D", "N" },
    { "R", "A", "A", "S", "F", "I" },
    { "H", "O", "D", "R", "L", "N" },
    { "E", "E", "E", "E", "A", "M" },
    { "He", "Qu", "Th", "In", "Er", "An" }
};
