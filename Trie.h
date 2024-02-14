#pragma once

#include <vector>
#include <string>

class Trie {
public:
	Trie(std::string filePath);
	~Trie();
	void printAllWords();
	std::string search(const std::string& word);
private:
	struct TrieElement {
		std::string wordSoFar;
		std::vector<TrieElement*> elements;
		bool isWordComplete;
	};

	TrieElement* root;
	void insert(TrieElement* p, std::string word);
	std::string parse(std::string word);
	void deleteAllTrieElements(TrieElement* p);
	void printAllWords(TrieElement* p);
};
