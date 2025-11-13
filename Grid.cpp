#include<iostream>
#include "Grid.h"
using namespace std;

void initializeGrid(char grid[10][10]){
    for (int i=0; i<GRID_SIZE; i++){
        for (int j=0; j<GRID_SIZE; j++){
            grid[i][j] = '_';
        }
    }
}


void printGrid(char grid[10][10]){
    for (int i=0; i<GRID_SIZE; i++){
        for (int j=0; j<GRID_SIZE; j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
}

// for horizontal placements

bool canPlaceHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c){
    int len = strlen(word);

    if(c<0 || c + len > GRID_SIZE) return false;

    for (int i=0; i<len; ++i){
        char g = grid[r][c+i];
        if (g != '_' && g != word[i]) return false;
    }

    return true;
}


void placeHorizontal(char grid [GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]){
    int len = strlen(word);

    for (int i=0; i<len; ++i){
        if (grid [r][c+i] == '_'){
            grid [r][c+i] = word[i];
            changed[i] = true;
        }

        else{
            changed[i] = false;
        }
    }
}


void unplaceHorizontal(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]){
    int len = strlen(word);

    for (int i=0; i<len; ++i){
        if (changed[i]){
            grid [r][c+i] = '_';
        }
    }
}


// for vertical placement

bool canPlaceVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c){
    int len = strlen(word);

    if (r < 0 || r+len > GRID_SIZE){
        return false;
    }
     
    for (int i=0; i<len; ++i){
        char g = grid[r+i][c];
        if (g != '_' && g != word[i]){
            return false;
        }
    }

    return true;
}


void placeVertical(char grid [GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]){
    int len = strlen(word);

    for (int i=0; i<len; ++i){
        if (grid [r+i][c] == '_'){
            grid [r+i][c] = word[i];
            changed[i] = true;
        }

        else{
            changed[i] = false;
        }
    }
}


void unplaceVertical(char grid[GRID_SIZE][GRID_SIZE], const char *word, int r, int c, bool changed[]){
    int len = strlen(word);

    for (int i=0; i<len; ++i){
        if (changed[i]){
            grid [r+i][c] = '_';
        }
    }
}




