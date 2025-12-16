
#ifndef GRID_H
#define GRID_H

#include <cstring>
#include "Dictionary.h"

const int GRID_SIZE = 12;

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE]);
void initializePlayerGrid(char grid[GRID_SIZE][GRID_SIZE]);   // <-- NEW
void printGrid(char grid[GRID_SIZE][GRID_SIZE]);


// New: print player grid with color comparing to solution
void printPlayerGrid(char playerGrid[GRID_SIZE][GRID_SIZE],
                     char solutionGrid[GRID_SIZE][GRID_SIZE]);

// Horizontal placement
bool canPlaceHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c);
void placeHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]);
void unplaceHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]);

// Vertical placement
bool canPlaceVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c);
void placeVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]);
void unplaceVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]);

// Backtracking
bool solveCrossword(char grid[GRID_SIZE][GRID_SIZE], char words[][MAX_LENGTH], int totalWords, int index);
bool generateCrossword(char grid[GRID_SIZE][GRID_SIZE], char words[][MAX_LENGTH], int totalWords);


bool revealRandomCell(char playerGrid[GRID_SIZE][GRID_SIZE],  
                      char solutionGrid[GRID_SIZE][GRID_SIZE]);
bool revealWordLetter(char playerGrid[GRID_SIZE][GRID_SIZE],
                      char solutionGrid[GRID_SIZE][GRID_SIZE],
                      char word[]);



#endif
