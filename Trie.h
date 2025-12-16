#ifndef TRIE_H
#define TRIE_H
#include "Dictionary.h"

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    void collectWords(TrieNode* node, char buffer[], int depth,
                      char result[][MAX_LENGTH], int &count);

public:
    Trie();
    void insert(const char word[]);
    bool search(const char word[]);
    void getRandomWords(char result[][MAX_LENGTH], int &count, int limit);
};

#endif
