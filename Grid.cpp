#include <iostream>
#include <algorithm>
#include <random>
#include <cstring>
#include "Grid.h"
#include "Dictionary.h"
using namespace std;

// Maintain same color codes as main
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

// initialize grid
void initializeGrid(char grid[GRID_SIZE][GRID_SIZE]){
    for (int i=0; i<GRID_SIZE; i++){
        for (int j=0; j<GRID_SIZE; j++){
            grid[i][j] = '_';
        }
    }
}

// print solved or puzzle grid (no coloring)
void printGrid(char grid[GRID_SIZE][GRID_SIZE]) {
    cout << "   ";
    for (int c = 0; c < GRID_SIZE; c++)
        cout << c << " ";
    cout << "\n";

    for (int r = 0; r < GRID_SIZE; r++) {
        cout << r << ": ";
        for (int c = 0; c < GRID_SIZE; c++) {
            cout << grid[r][c] << " ";
        }
        cout << "\n";
    }
}

// NEW: print player grid with colored cells compared to solutionGrid
void printPlayerGrid(char playerGrid[GRID_SIZE][GRID_SIZE],
                     char solutionGrid[GRID_SIZE][GRID_SIZE]) {
    cout << "   ";
    for (int c = 0; c < GRID_SIZE; c++) cout << c << ' ';
    cout << '\n';

    for (int r = 0; r < GRID_SIZE; r++) {
        cout << r << ": ";
        for (int c = 0; c < GRID_SIZE; c++) {
            char p = playerGrid[r][c];
            char s = solutionGrid[r][c];
            if (p == '_') {
                cout << CYAN << p << RESET << ' ';
            } else {
                if (s != '_' && p == s) cout << GREEN << p << RESET << ' ';
                else cout << RED << p << RESET << ' ';
            }
        }
        cout << '\n';
    }
}

// ---------------- horizontal placement ----------------
bool canPlaceHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c)
{
    int len = strlen(word);

    // fits?
    if (c < 0 || c + len > GRID_SIZE) return false;

    // left/right boundary checks to avoid adjacent words
    if (c - 1 >= 0 && grid[r][c - 1] != '_') return false;
    if (c + len < GRID_SIZE && grid[r][c + len] != '_') return false;

    for (int i = 0; i < len; i++) {
        char g = grid[r][c + i];

        // conflict: existing letter that doesn't match
        if (g != '_' && g != word[i]) return false;

        // adjacent above/below should be empty unless that same cell is matching letter (allow crossings)
        if (r - 1 >= 0 && grid[r - 1][c + i] != '_') return false;
        if (r + 1 < GRID_SIZE && grid[r + 1][c + i] != '_') return false;
    }

    return true;
}

void placeHorizontal(char grid [GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]){
    int len = strlen(word);
    for (int i=0;i<len;++i){
        if (grid[r][c+i] == '_') { grid[r][c+i] = word[i]; changed[i] = true; }
        else changed[i] = false;
    }
}

void unplaceHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]){
    int len = strlen(word);
    for (int i=0;i<len;++i) if (changed[i]) grid[r][c+i] = '_';
}

// ---------------- vertical ----------------
bool canPlaceVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c)
{
    int len = strlen(word);
    if (r < 0 || r + len > GRID_SIZE) return false;

    if (r - 1 >= 0 && grid[r - 1][c] != '_') return false;
    if (r + len < GRID_SIZE && grid[r + len][c] != '_') return false;

    for (int i = 0; i < len; i++) {
        char g = grid[r + i][c];
        if (g != '_' && g != word[i]) return false;

        if (c - 1 >= 0 && grid[r + i][c - 1] != '_') return false;
        if (c + 1 < GRID_SIZE && grid[r + i][c + 1] != '_') return false;
    }
    return true;
}

void placeVertical(char grid [GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]){
    int len = strlen(word);
    for (int i=0;i<len;++i){
        if (grid[r+i][c] == '_') { grid[r+i][c] = word[i]; changed[i] = true; }
        else changed[i] = false;
    }
}

void unplaceVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]){
    int len = strlen(word);
    for (int i=0;i<len;++i) if (changed[i]) grid[r+i][c] = '_';
}

// tryPlace / undoWord (helper)
bool tryPlaceWord(char grid[GRID_SIZE][GRID_SIZE], const char* word, int r, int c, bool changed[], bool horizontal)
{
    if (horizontal) {
        if (!canPlaceHorizontal(grid, word, r, c)) return false;
        placeHorizontal(grid, word, r, c, changed);
        return true;
    } else {
        if (!canPlaceVertical(grid, word, r, c)) return false;
        placeVertical(grid, word, r, c, changed);
        return true;
    }
}
void undoWord(char grid[GRID_SIZE][GRID_SIZE], const char* word, int r, int c, bool changed[], bool horizontal)
{
    if (horizontal) unplaceHorizontal(grid, word, r, c, changed);
    else unplaceVertical(grid, word, r, c, changed);
}

// ---------------- backtracking solver ----------------
bool solveCrossword(char grid[GRID_SIZE][GRID_SIZE], char words[][MAX_LENGTH], int totalWords, int index)
{
    if (index == totalWords) return true;
    const char* word = words[index];

    for (int r = 0; r < GRID_SIZE; ++r) {
        for (int c = 0; c < GRID_SIZE; ++c) {
            bool changed[20];
            if (tryPlaceWord(grid, word, r, c, changed, true)) {
                if (solveCrossword(grid, words, totalWords, index + 1)) return true;
                undoWord(grid, word, r, c, changed, true);
            }
            if (tryPlaceWord(grid, word, r, c, changed, false)) {
                if (solveCrossword(grid, words, totalWords, index + 1)) return true;
                undoWord(grid, word, r, c, changed, false);
            }
        }
    }
    return false;
}

// ---------------- improved generateCrossword wrapper ----------------
// tries multiple shuffles of the word order to improve success chance
bool generateCrossword(char grid[GRID_SIZE][GRID_SIZE], char words[][MAX_LENGTH], int totalWords)
{
    vector<int> order(totalWords);
    for (int i = 0; i < totalWords; ++i) order[i] = i;

    const int attempts = 40; // try 40 different orders
    random_device rd;
    mt19937 g(rd());

    for (int a = 0; a < attempts; ++a) {
        initializeGrid(grid);

        shuffle(order.begin(), order.end(), g);

        // create temporary ordered words array
        char tmp[MAX_WORDS][MAX_LENGTH];
        for (int i = 0; i < totalWords; ++i) strcpy(tmp[i], words[order[i]]);

        if (solveCrossword(grid, tmp, totalWords, 0)) return true;
    }
    return false;
}

// hidden player grid
void initializePlayerGrid(char playerGrid[GRID_SIZE][GRID_SIZE]) {
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {
            playerGrid[r][c] = '_';   // Hide all letters
        }
    }
}