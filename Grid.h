#ifndef GRID_H
#define GRID_H

#include<cstring>

const int GRID_SIZE = 10;

void initializeGrid(char grid[GRID_SIZE][GRID_SIZE]);
void printGrid(char grid[GRID_SIZE][GRID_SIZE]);

// for horizontal placement

bool canPlaceHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c);

void placeHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]);

void unplaceHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]);

// for vertical placement

bool canPlaceVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c);

void placeVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]);

void unplaceVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]);

#endif