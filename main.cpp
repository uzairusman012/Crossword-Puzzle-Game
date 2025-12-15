#include<iostream>
#include "Grid.h"
#include "Dictionary.h"
using namespace std;

int main(){
    cout<<"============ Crossword Puzzle Game ============"<<endl;
    cout<< " Hello Husnain\n";

    // creating the crossword grid

    char grid[GRID_SIZE][GRID_SIZE];

    initializeGrid(grid);
    printGrid(grid);

    // loading words from the file

    char words[MAX_WORDS][MAX_LENGTH];
    int total = loadWords("words.txt",words);

    // printing words

    if (total==0){
        cout<<"No words loaded "<<endl;
        return 0;
    } else{

    printWords(words, total);

}
    // testing some words

    const char *w1 = words[0];
    const char *w2 = words[1];

    bool changed1[20];
    bool changed2[20];

    if (canPlaceHorizontal(grid, w1, 2, 1)){
        placeHorizontal(grid, w1, 2, 1, changed1);
        printGrid(grid);

        if (canPlaceVertical(grid, w2, 0, 3)){
            placeVertical(grid, w2, 0, 3, changed2);
            printGrid(grid);
        }
    }

  
}