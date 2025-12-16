#include "Trie.h"
#include "Dictionary.h"
#include <cstdlib>
#include <ctime>
#include <cstring>

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const char word[]) {
    TrieNode* curr = root;

    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        if (!curr->children[index])
            curr->children[index] = new TrieNode();
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

bool Trie::search(const char word[]) {
    TrieNode* curr = root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        if (!curr->children[index])
            return false;
        curr = curr->children[index];
    }
    return curr->isEndOfWord;
}

// Helper: DFS to collect all words
void Trie::collectWords(TrieNode* node, char buffer[], int depth,
                        char result[][MAX_LENGTH], int &count) {
    if (!node) return;

    if (node->isEndOfWord) {
        buffer[depth] = '\0';
        strcpy(result[count++], buffer);
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            buffer[depth] = i + 'a';
            collectWords(node->children[i], buffer, depth + 1, result, count);
        }
    }
}

// Pick RANDOM words from Trie
void Trie::getRandomWords(char result[][MAX_LENGTH], int &count, int limit) {
    char allWords[MAX_WORDS][MAX_LENGTH];
    int total = 0;
    char buffer[MAX_LENGTH];

    collectWords(root, buffer, 0, allWords, total);

    srand(time(NULL));

    count = (limit < total) ? limit : total;

    for (int i = 0; i < count; i++) {
        int idx = rand() % total;
        strcpy(result[i], allWords[idx]);
    }
}
