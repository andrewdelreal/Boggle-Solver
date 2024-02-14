#include "Trie.h"

#include <fstream>
#include <iostream>

Trie::Trie(std::string filePath) {
	std::ifstream file(filePath);
	root = new TrieElement();
	root->wordSoFar = "";
	root->isWordComplete = false;
	root->elements.resize(26, 0);

	if (file.is_open()) {
		std::string unParsedWord;
		while (std::getline(file, unParsedWord)) {
			std::string parsedWord = parse(unParsedWord);
			insert(root, parsedWord);
		}
		file.close();
	}
	else {
		std::cerr << "File failed to open." << std::endl;
	}
	
}

void Trie::insert(TrieElement* p, std::string word) {
	if (word != "") {
		char firstCharacter = word.front();
		std::string rest = word.substr(1);
		int index = firstCharacter - 'a';

		if (p->elements.at(index) == 0) {
			TrieElement* temp = new TrieElement();
			temp->elements.resize(26, 0);
			temp->wordSoFar = p->wordSoFar + firstCharacter;
			if (rest == "") {
				temp->isWordComplete = true;
			}
			else {
				temp->isWordComplete = false;
			}
			p->elements.at(index) = temp;
			insert(temp, rest);
		}
		else {
			insert(p->elements.at(index), rest);
		}
	}
}

std::string Trie::parse(std::string word) {
	std::string retval;
	for (size_t i = 0; i < word.size(); i++) {
		if (isalpha(word.at(i))) {
			retval.push_back(tolower(word.at(i)));
		}
	}
	return retval;
}

Trie::~Trie() {
	deleteAllTrieElements(root);
	//std::cout << "\tDeleting " << "root" << " vector\n";
	delete root;
}

void Trie::deleteAllTrieElements(TrieElement* p) {
	for (size_t i = 0; i < p->elements.size(); i++) {
		if (p->elements.at(i) != 0) {
			deleteAllTrieElements(p->elements.at(i));
			TrieElement* p_delete = p->elements.at(i);
			p->elements.at(i) = 0;
			//std::cout << "\tDeleting " << p_delete->wordSoFar << " vector\n";
			delete p_delete;
		}
	}
}

void Trie::printAllWords() {
	printAllWords(root);
}

void Trie::printAllWords(TrieElement* p) {
	for (size_t i = 0; i < p->elements.size(); i++) {
		if (p->elements.at(i) != 0) {
			if (p->elements.at(i)->isWordComplete) {
				std::cout << p->elements.at(i)->wordSoFar << " ";
			}
			printAllWords(p->elements.at(i));
		}
	}
}

std::string Trie::search(const std::string& word) {
	std::string parsedWord = parse(word);
	int pos = parsedWord.at(0) - 'a';
	TrieElement* p = root;
	for (size_t i = 0; i < parsedWord.size(); i++) {
		pos = parsedWord.at(i) - 'a';
		if (p->elements.at(pos) == 0) {
			return "NOT FOUND";
		}
		else {
			if (i == parsedWord.size() - 1 && p->elements.at(pos)->isWordComplete) {
				return "FOUND";
			}
			else if (i == parsedWord.size() - 1) {
				return "PARTIAL";
			}
		}
		
		p = p->elements.at(pos);
	}
}
