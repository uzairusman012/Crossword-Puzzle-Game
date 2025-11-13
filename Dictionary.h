#ifndef DICTIONARY_H
#define DICTIONARY_H

const int MAX_WORDS = 100;
const int MAX_LENGTH = 20;

int loadWords(const char filename[], char words[][MAX_LENGTH]);
void printWords(char words[][MAX_LENGTH], int totalWords);

#endif