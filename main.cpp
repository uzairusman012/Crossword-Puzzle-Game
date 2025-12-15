#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits>   // for input clearing
#include <fstream>
#include "Trie.h"




#include "Grid.h"
#include "Dictionary.h"

using namespace std;
enum Difficulty { EASY, MEDIUM, HARD };
// ===== COLOR CODES =====
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define MAGENTA "\033[35m"

// ===== CLEAR SCREEN =====
// void clearScreen() {
//     #ifdef _WIN32
//         system("cls");
//     #else
//         system("clear");
//     #endif
// }

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

// ===== PAUSE =====
void pauseScreen() {
    cout << "\n" << YELLOW << "Press Enter to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ===== WORD SHUFFLE =====
void shuffleWords(char words[][MAX_LENGTH], int total) {
    srand((unsigned int) time(NULL));

    char temp[MAX_LENGTH];
    for (int i = total - 1; i > 0; --i) {
        int j = rand() % (i + 1);

        strcpy(temp, words[i]);
        strcpy(words[i], words[j]);
        strcpy(words[j], temp);
    }
}

// ===== DISPLAY WORD LIST =====
void showWordList(char words[][MAX_LENGTH], int total) {
    cout << CYAN << "\n===== WORD LIST =====\n" << RESET;
    printWords(words, total);
}

// ===== MENU FUNCTION =====
void showMenu() {
    cout << BLUE 
         << "\n================== CROSSWORD MENU ==================\n"
         << RESET;

    cout << YELLOW;
    cout << "1. Show Word List\n";
    cout << "2. Shuffle Words\n";
    cout << "3. Generate Crossword\n";
    cout << "4. Display Crossword Grid\n";
    cout << "5. Save Crossword to File\n";
    cout<<  "6. Play Crossword\n";
    cout << "7. Exit Program\n";
    cout << "8. Temporary Test\n";
    cout << RESET;

    cout << BLUE << "====================================================\n" << RESET;
    cout << GREEN << "Enter choice: " << RESET;
}


void saveCrosswordToFile(char grid[GRID_SIZE][GRID_SIZE], char words[][MAX_LENGTH], int totalWords) {
    ofstream fout("puzzle.txt");

    if (!fout) {
        cout << RED << "Error: Could not create puzzle.txt\n" << RESET;
        return;
    }

    fout << "=========== CROSSWORD PUZZLE ===========\n\n";

    // Write grid
    fout << "Grid (" << GRID_SIZE << "x" << GRID_SIZE << "):\n";
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {
            fout << grid[r][c] << ' ';
        }
        fout << "\n";
    }

    fout << "\n=========== WORD LIST ===========\n";
    for (int i = 0; i < totalWords; i++) {
        fout << (i + 1) << ". " << words[i] << "\n";
    }

    fout << "\nGenerated using Crossword Generator Project\n";

    fout.close();

    cout << GREEN << "Crossword saved to puzzle.txt successfully!\n" << RESET;
}

// ===== SAVE HIGH SCORE =====
void saveScore(int score) {
    ofstream fout("highscores.txt", ios::app);
    if (!fout) return;

    // Get current date
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char dateStr[20];
    sprintf(dateStr, "%04d-%02d-%02d", 1900+ltm->tm_year, 1+ltm->tm_mon, 1+ltm->tm_mday);

    fout << score << " " << dateStr << "\n";
    fout.close();
}

// ===== PLAYER MODE HELPERS =====

// Check whether cell r,c in solution contains a letter (not underscore)
bool isCellPartOfAnyWord(char solutionGrid[GRID_SIZE][GRID_SIZE], int r, int c) {
    if (r < 0 || r >= GRID_SIZE || c < 0 || c >= GRID_SIZE) return false;
    return solutionGrid[r][c] != '_';
}

// Place a letter entered by player and return whether it's correct
bool placePlayerLetter(char playerGrid[GRID_SIZE][GRID_SIZE],
                       char solutionGrid[GRID_SIZE][GRID_SIZE],
                       int r, int c, char letter) {
    if (r < 0 || r >= GRID_SIZE || c < 0 || c >= GRID_SIZE) return false;
    // only allow placing in cells that are part of the puzzle
    if (!isCellPartOfAnyWord(solutionGrid, r, c)) return false;

    // normalize letter (if you used lowercase in solution, keep same)
    // assume solution uses lowercase; convert input
    if (letter >= 'A' && letter <= 'Z') letter = letter - 'A' + 'a';

    playerGrid[r][c] = letter;
    return playerGrid[r][c] == solutionGrid[r][c];
}

// Check if playerGrid equals solutionGrid
bool isPuzzleSolved(char playerGrid[GRID_SIZE][GRID_SIZE],
                    char solutionGrid[GRID_SIZE][GRID_SIZE]) {
    for (int r = 0; r < GRID_SIZE; ++r) {
        for (int c = 0; c < GRID_SIZE; ++c) {
            // if solution has letter and player does not match -> not solved
            if (solutionGrid[r][c] != '_' && playerGrid[r][c] != solutionGrid[r][c])
                return false;
        }
    }
    return true;
}


bool revealRandomCell(char playerGrid[GRID_SIZE][GRID_SIZE],  
                      char solutionGrid[GRID_SIZE][GRID_SIZE])    // Reveal any random unfilled correct letter 
{
    int positions[200][2];
    int count = 0;

    // Collect all hidden correct cell positions
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {

            if (solutionGrid[r][c] != '_' && playerGrid[r][c] != solutionGrid[r][c]) {
                positions[count][0] = r;
                positions[count][1] = c;
                count++;
            }
        }
    }

    if (count == 0) return false;

    int idx = rand() % count;
    int rr = positions[idx][0];
    int cc = positions[idx][1];

    playerGrid[rr][cc] = solutionGrid[rr][cc];
    return true;
}

void showDetailedProgress(char playerGrid[GRID_SIZE][GRID_SIZE],
                          char solutionGrid[GRID_SIZE][GRID_SIZE]) // Show detailed progress 
{
    int totalLetters = 0, correctLetters = 0;

    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {

            if (solutionGrid[r][c] != '_') {
                totalLetters++;
                if (playerGrid[r][c] == solutionGrid[r][c]) {
                    correctLetters++;
                }
            }
        }
    }

    int remaining = totalLetters - correctLetters;
    double percent = (correctLetters * 100.0) / totalLetters;

    cout << CYAN << "\n===== PROGRESS REPORT =====\n" << RESET;
    cout << "Correct letters: " << correctLetters << "/" << totalLetters << "\n";
    cout << "Letters remaining: " << remaining << "\n";
    cout << "Completion: " << percent << "%\n";
}

bool revealWordLetter(char playerGrid[GRID_SIZE][GRID_SIZE],
                      char solutionGrid[GRID_SIZE][GRID_SIZE],
                      char word[])  // Reveal one letter from a selected word
{
    int len = strlen(word);

    int matches[20][2];
    int count = 0;

    // Search entire grid for letter positions belonging to this word
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {

            if (solutionGrid[r][c] == '_') continue;

            // Compare letter-by-letter (case-insensitive)
            for (int i = 0; i < len; i++) {
                char sol = solutionGrid[r][c];
                if (sol >= 'A' && sol <= 'Z') sol += 32;
                char w = word[i];
                if (w >= 'A' && w <= 'Z') w += 32;

                if (sol == w) {
                    if (playerGrid[r][c] != solutionGrid[r][c]) {
                        matches[count][0] = r;
                        matches[count][1] = c;
                        count++;
                    }
                }
            }
        }
    }

    if (count == 0) return false;

    int idx = rand() % count;
    playerGrid[matches[idx][0]][matches[idx][1]] = solutionGrid[matches[idx][0]][matches[idx][1]];
    return true;
}


Difficulty selectDifficulty() {
    int choice;
    cout << "\nSelect Difficulty Level:\n";
    cout << "1. Easy (40% letters revealed)\n";
    cout << "2. Medium (20% letters revealed)\n";
    cout << "3. Hard (no letters revealed)\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch(choice) {
        case 1: return EASY;
        case 2: return MEDIUM;
        case 3: return HARD;
        default: return MEDIUM;
    }
}

void revealLettersByDifficulty(char playerGrid[GRID_SIZE][GRID_SIZE],
                               char solutionGrid[GRID_SIZE][GRID_SIZE],
                               Difficulty diff) {
    int totalCells = 0;

    // Count total letters in solution
    for (int r = 0; r < GRID_SIZE; r++)
        for (int c = 0; c < GRID_SIZE; c++)
            if (solutionGrid[r][c] != '_')
                totalCells++;

    int revealCount = 0;
    if (diff == EASY) revealCount = totalCells * 40 / 100;
    else if (diff == MEDIUM) revealCount = totalCells * 20 / 100;
    else revealCount = 0;  // Hard

    srand((unsigned int) time(NULL));
    while (revealCount > 0) {
        int r = rand() % GRID_SIZE;
        int c = rand() % GRID_SIZE;
        if (solutionGrid[r][c] != '_' && playerGrid[r][c] == '_') {
            playerGrid[r][c] = solutionGrid[r][c];
            revealCount--;
        }
    }
}



// void playMode(char solutionGrid[GRID_SIZE][GRID_SIZE],
//               char playerGrid[GRID_SIZE][GRID_SIZE],
//               char words[][MAX_LENGTH],
//               int totalWords)
void playMode(char solutionGrid[GRID_SIZE][GRID_SIZE],
              char playerGrid[GRID_SIZE][GRID_SIZE],
              char gameWords[][MAX_LENGTH],
              int gameWordCount){
    int score = 0;
    int lives = 3;
    int choice = 0;

    // int randomHintLimit = 10;   // max 3 random reveals
    // int wordHintLimit = 1;     // max 1 reveal per word per game

    // Track per-word hints
    // int wordUsedHint[MAX_WORDS] = {0};


    // ======== DIFFICULTY SYSTEM ========
    cout << CYAN << "Select Difficulty Level:\n" << RESET;
    cout << "1. Easy (40% letters revealed)\n";
    cout << "2. Medium (20% letters revealed)\n";
    cout << "3. Hard (no letters revealed)\n";
    cout << GREEN << "Enter choice: " << RESET;

    int diffChoice;
    cin >> diffChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int revealPercent = 0;
    int randomHintLimit ; // default hints
    int wordHintLimit = 1;

    if (diffChoice == 1) { // Easy
        revealPercent = 60;
        randomHintLimit = 10;
    } else if (diffChoice == 2) { // Medium
        revealPercent = 50;
        randomHintLimit = 2;
    } else { // Hard
        revealPercent = 40;
        randomHintLimit = 4;
        wordHintLimit = 2;
    }

    // ======== INITIAL LETTER REVEAL ========
    int totalCells = 0;
    for (int r = 0; r < GRID_SIZE; r++)
        for (int c = 0; c < GRID_SIZE; c++)
            if (solutionGrid[r][c] != '_') totalCells++;

    int lettersToReveal = (totalCells * revealPercent) / 100;

    while (lettersToReveal > 0) {
        int r = rand() % GRID_SIZE;
        int c = rand() % GRID_SIZE;
        if (solutionGrid[r][c] != '_' && playerGrid[r][c] == '_') {
            playerGrid[r][c] = solutionGrid[r][c];
            lettersToReveal--;
        }
    }

    // Track per-word hints
    int wordUsedHint[MAX_WORDS] = {0};

    // ======== GAME LOOP ========

    while (true) {

        clearScreen();
        // Header UI
        cout << CYAN << "=========== PLAYER MODE ===========\n" << RESET;
        cout << "Lives: " << lives << "   |   Score: " << score 
             << "   |   Random Hints Left: " << randomHintLimit << "\n";
        cout << "====================================\n\n";

        // Display grid
        // cout << CYAN << "Your Puzzle:\n" << RESET;
        // printGrid(playerGrid);
        cout << CYAN << "Your Puzzle:\n" << RESET;
        printPlayerGrid(playerGrid, solutionGrid);

        // Menu
        cout << "\nOptions:\n";
        cout << "1. Place a letter\n";
        cout << "2. Check progress\n";
        cout << "3. Reveal a random correct letter (Hint)\n";
        cout << "4. Reveal a letter from a specific word\n";
        cout << "5. Detailed progress report\n";
        cout << "6. Quit to main menu\n";
        cout << GREEN << "Enter choice: " << RESET;

        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // ============================
        // 1. Place a letter
        // ============================
        if (choice == 1) {
            int r, c;
            char ch;

            cout << "Enter row (0–" << GRID_SIZE - 1 << "): ";
            cin >> r;
            cout << "Enter column (0–" << GRID_SIZE - 1 << "): ";
            cin >> c;
            cout << "Enter letter: ";
            cin >> ch;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!isCellPartOfAnyWord(solutionGrid, r, c)) {
                cout << RED << "This cell is not part of the crossword.\n" << RESET;
                pauseScreen();
                continue;
            }

            bool correct = placePlayerLetter(playerGrid, solutionGrid, r, c, ch);
            if (correct) {
                cout << GREEN << "Correct!\n" << RESET;
                score++;
            } else {
                cout << RED << "Incorrect!\n" << RESET;
                score--;
                lives--;
                cout << YELLOW << "Lives left: " << lives << "\n" << RESET;

                if (lives == 0) {
                    cout << RED << "\nGAME OVER! You ran out of lives.\n" << RESET;
                    cout << CYAN << "\nCorrect Solution:\n" << RESET;
                    printGrid(solutionGrid);
                    pauseScreen();
                    break;
                }
            }

            if (isPuzzleSolved(playerGrid, solutionGrid)) {
                cout << GREEN << "\nCongratulations! You solved the puzzle!\n" << RESET;
                cout << "Final Score: " << score << "\n";
                saveScore(score);
                cout << GREEN << "Your score has been saved!\n" << RESET;
                pauseScreen();
                break;
            }
            pauseScreen();
        }

        // ============================
        // 2. Simple progress
        // ============================
        else if (choice == 2) {
            int totalLetters = 0, correctLetters = 0;
            for (int r = 0; r < GRID_SIZE; ++r) {
                for (int c = 0; c < GRID_SIZE; ++c) {
                    if (solutionGrid[r][c] != '_') {
                        totalLetters++;
                        if (playerGrid[r][c] == solutionGrid[r][c])
                            correctLetters++;
                    }
                }
            }
            cout << CYAN << "Progress: " << correctLetters << " / " << totalLetters << "\n" << RESET;
            pauseScreen();
        }

        // ============================
        // 3. Random reveal hint
        // ============================
        else if (choice == 3) {
            if (randomHintLimit <= 0) {
                cout << YELLOW << "No random hints remaining.\n" << RESET;
                pauseScreen();
                continue;
            }

            if (revealRandomCell(playerGrid, solutionGrid)) {
                randomHintLimit--;
                cout << GREEN << "A random letter has been revealed!\n" << RESET;
            } else {
                cout << YELLOW << "No letters left to reveal.\n" << RESET;
            }
            pauseScreen();
        }

        // ============================
        // 4. Word-specific hint
        // ============================
        else if (choice == 4) {
            // cout << CYAN << "Enter word number (1–" << totalWords << "): " << RESET;
            cout << CYAN << "Enter word number (1–" << gameWordCount << "): " << RESET;
            int w;
            cin >> w;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // if (w < 1 || w > totalWords) 
            if (w < 1 || w > gameWordCount){
                cout << RED << "Invalid word number.\n" << RESET;
                pauseScreen();
                continue;
            }
            
            // limit to 1 hint per word
            if (wordUsedHint[w - 1] >= wordHintLimit) {
                cout << YELLOW << "You already used a hint for this word.\n" << RESET;
                pauseScreen();
                continue;
            }

            // if (revealWordLetter(playerGrid, solutionGrid, words[w - 1])) 
            if (revealWordLetter(playerGrid, solutionGrid, gameWords[w - 1])){
                wordUsedHint[w - 1]++;
                // cout << GREEN << "One letter from \"" << words[w - 1]
                cout << GREEN << "One letter from \"" << gameWords[w - 1] 
                     << "\" has been revealed!\n" << RESET;
            } else {
                cout << YELLOW << "No hidden letters left for this word.\n" << RESET;
            }

            pauseScreen();
        }

        // ============================
        // 5. Detailed progress
        // ============================
        else if (choice == 5) {
            showDetailedProgress(playerGrid, solutionGrid);
            pauseScreen();
        }

        // ============================
        // 6. Quit
        // ============================
        else if (choice == 6) {
            cout << YELLOW << "Exiting player mode...\n" << RESET;
            pauseScreen();
            break;
        }

        else {
            cout << RED << "Invalid choice.\n" << RESET;
            pauseScreen();
        }
    }
}

// ===========================
//  MAIN PROGRAM
// ===========================
int main() {

    Trie trie;
    // Load dictionary words
    char words[MAX_WORDS][MAX_LENGTH];
    int total = loadWords("words.txt", words);

    // Insert into Trie
    for (int i = 0; i < total; i++) {
        trie.insert(words[i]);
    }
    


    if (total <= 0) {
        cout << RED << "Error: No words loaded from words.txt!\n" << RESET;
        return 0;
    }

    // Grid to store crossword
    char grid[GRID_SIZE][GRID_SIZE];
    initializeGrid(grid);

    // ADD THESE NEW VARIABLES at top of main() after loading words:

    // char grid[GRID_SIZE][GRID_SIZE];         // final crossword (old)
    char solutionGrid[GRID_SIZE][GRID_SIZE];   // correct answers
    char playerGrid[GRID_SIZE][GRID_SIZE];    // what player sees

    char gameWords[MAX_WORDS][MAX_LENGTH];
    int gameWordCount = 0;

    initializeGrid(grid);
    initializePlayerGrid(playerGrid);

    bool gridGenerated = false;

    int choice;

    while (true) {
        clearScreen();
        showMenu();
        cin >> choice;

        // Fix input issues
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

        clearScreen();

        switch (choice) {

        case 1:  // Show word list
            showWordList(words, total);
            pauseScreen();
            break;

        case 2:  // Shuffle words
            cout << GREEN << "Shuffling words...\n" << RESET;
            shuffleWords(words, total);
            cout << CYAN << "Words After Shuffle:\n" << RESET;
            printWords(words, total);
            pauseScreen();
            break;

        case 3:  // Generate crossword
            // cout << GREEN << "Generating crossword using backtracking...\n" << RESET;

            // initializeGrid(grid);

            // if (generateCrossword(grid, words, total)) {
            //     cout << GREEN << "Crossword Successfully Generated!\n\n" << RESET;
            //     printGrid(grid);
            //     gridGenerated = true;
            // } else {
            //     cout << RED << "Failed to generate crossword.\n" << RESET;
            // }
            // pauseScreen();
            // break;
            // cout << GREEN << "Generating crossword using backtracking...\n" << RESET;

            // initializeGrid(grid);
            

            // if (generateCrossword(grid, words, total)) {
            //     cout << GREEN << "Crossword Successfully Generated!\n\n" << RESET;
            //         printGrid(grid);
            //     gridGenerated = true;

            //     // Copy the solved crossword to solutionGrid
            //     memcpy(solutionGrid, grid, sizeof(solutionGrid));

            //     // Reset player grid (hidden)
            //     initializePlayerGrid(playerGrid);
            //     } 
            // else {
            //         cout << RED << "Failed to generate crossword.\n" << RESET;
            // }
            // pauseScreen();
            // break;

            cout << GREEN << "Generating crossword using backtracking...\n" << RESET;

                initializeGrid(grid);

                // ==============================
                // PICK RANDOM WORDS FROM TRIE
                // ==============================
                

                trie.getRandomWords(gameWords, gameWordCount, 15); // pick 15 random words

                // ==============================
                // GENERATE CROSSWORD USING RANDOM WORDS
                // ==============================
                if (generateCrossword(grid, gameWords, gameWordCount)) {
                     cout << GREEN << "Crossword Successfully Generated!\n\n" << RESET;
                    printGrid(grid);

                    gridGenerated = true;

                    //     Save solution
                     memcpy(solutionGrid, grid, sizeof(solutionGrid));

                 // Reset player grid
                  initializePlayerGrid(playerGrid);
                } 
                else {
                    cout << RED << "Failed to generate crossword.\n" << RESET;
                }

               pauseScreen();
               break;
        case 4:  // Display crossword grid
            if (!gridGenerated) {
                cout << RED << "No crossword generated yet!\n" << RESET;
            } else {
                cout << CYAN << "===== CROSSWORD GRID =====\n\n" << RESET;
                // printGrid(grid);
                printPlayerGrid(playerGrid, solutionGrid);
            }
            pauseScreen();
            break;

        case 5:  // Save crossword
            if (!gridGenerated) {
                cout << RED << "No crossword generated to save!\n" << RESET;
            } else {
                saveCrosswordToFile(grid, words, total);
            }
            pauseScreen();
            break;
        case 6: // Play Crossword
            if (!gridGenerated) {
                cout << RED << "No crossword generated yet! Please generate a crossword first.\n" << RESET;
                pauseScreen();
            } else {
                // ensure solutionGrid and playerGrid exist and are current
                // (we used memcpy earlier when generating)
                // playMode(solutionGrid, playerGrid, words, total);
                playMode(solutionGrid, playerGrid, gameWords, gameWordCount);
            }
            break;
        case 7: // Exit
            cout << GREEN << "Exiting program... Goodbye!\n" << RESET;
            return 0;

        case 8: // TEMPORARY test
            cout << MAGENTA << "--- SOLUTION GRID ---\n" << RESET;
            printGrid(solutionGrid);

            cout << CYAN << "\n--- PLAYER GRID (EMPTY) ---\n" << RESET;
            printGrid(playerGrid);

            // for testing only 
            cout << MAGENTA << "--- SOLUTION GRID ---\n" << RESET;
            printGrid(solutionGrid);

            cout << CYAN << "\n--- PLAYER GRID (colored) ---\n" << RESET;
            printPlayerGrid(playerGrid, solutionGrid);
            pauseScreen();
            break;
        default:
            cout << RED << "Invalid choice!\n" << RESET;
            pauseScreen();
        }
    }

    return 0;
}

//   g++ Dictionary.cpp Grid.cpp main.cpp -o Crossword
//   g++ Dictionary.cpp Grid.cpp Trie.cpp main.cpp -o Crossword
//   .\Crossword