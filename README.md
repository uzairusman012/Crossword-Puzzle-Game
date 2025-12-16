# 🧩 Crossword Puzzle Generator Game

A comprehensive C++ console-based crossword puzzle generator and interactive game that uses advanced data structures and backtracking algorithms to create and solve crossword puzzles.

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [How to Run](#how-to-run)
- [Usage Guide](#usage-guide)
- [Game Modes](#game-modes)
- [Technical Details](#technical-details)
- [File Descriptions](#file-descriptions)
- [Dependencies](#dependencies)
- [Future Enhancements](#future-enhancements)

---

## 🎯 Overview

This project is an intelligent crossword puzzle generator that creates solvable puzzles from a custom word list. It features an interactive gameplay mode with multiple difficulty levels, hint systems, and score tracking. The program uses a Trie data structure for efficient word storage and a backtracking algorithm for puzzle generation.

## ✨ Features

### Core Features
- **Automatic Crossword Generation**: Uses backtracking algorithm to create valid crossword puzzles
- **Trie Data Structure**: Efficient word storage and retrieval
- **Random Word Selection**: Picks random words from dictionary for varied puzzles
- **Interactive Gameplay**: Player mode with letter-by-letter input
- **Multiple Difficulty Levels**:
  - Easy (60% letters revealed)
  - Medium (50% letters revealed)
  - Hard (40% letters revealed)

### Gameplay Features
- **Color-Coded Feedback**:
  - 🟢 Green: Correct letters
  - 🔴 Red: Incorrect letters
  - 🔵 Cyan: Empty cells
- **Hint System**:
  - Random cell reveal
  - Word-specific letter reveal
  - Limited hints based on difficulty
- **Lives System**: 3 lives per game
- **Score Tracking**: Points for correct answers, penalties for mistakes
- **Progress Reports**: Detailed completion statistics
- **Save Feature**: Export puzzles to text files
- **High Score System**: Persistent score tracking

### User Interface
- **Colored Console Output**: Enhanced visual experience
- **Clear Screen Management**: Clean interface transitions
- **Menu-Driven Navigation**: Easy-to-use interface
- **Input Validation**: Robust error handling

---

## 📁 Project Structure

```
crossword/
│
├── Dictionary.cpp         # Word loading and dictionary management
├── Dictionary.h           # Dictionary header file
├── Grid.cpp               # Grid operations and puzzle generation
├── Grid.h                 # Grid header file
├── Trie.cpp               # Trie data structure implementation
├── Trie.h                 # Trie header file
├── main.cpp               # Main program and game logic
├── words.txt              # Word dictionary file
├── puzzle.txt             # Generated puzzle output (created at runtime)
├── highscores.txt         # High scores storage (created at runtime)
└── README.md              # Project documentation
```

---

## 🔧 Installation

### Prerequisites
- C++ Compiler (GCC/G++, MinGW, or Visual Studio)
- C++11 or higher
- Terminal/Console that supports ANSI color codes

### Steps

1. **Clone or Download** the project files to your local directory

2. **Ensure all files are present**:
   - All `.cpp` and `.h` files
   - `words.txt` file with word list

3. **Verify word list**: Make sure `words.txt` contains valid words (one per line, lowercase preferred)

---

## 🚀 How to Run

### Compilation

**Windows (MinGW/GCC):**
```bash
g++ Dictionary.cpp Grid.cpp Trie.cpp main.cpp -o Crossword
.\Crossword
```

**Linux/Mac:**
```bash
g++ Dictionary.cpp Grid.cpp Trie.cpp main.cpp -o Crossword
./Crossword
```

**Visual Studio:**
1. Create a new Console Application project
2. Add all `.cpp` files to the project
3. Build and run (Ctrl+F5)

---

## 📖 Usage Guide

### Main Menu Options

```
1. Show Word List        - Display all loaded words from dictionary
2. Shuffle Words         - Randomize word order
3. Generate Crossword    - Create a new crossword puzzle
4. Display Crossword     - View the current puzzle grid
5. Save Crossword        - Export puzzle to puzzle.txt
6. Play Crossword        - Enter interactive game mode
7. Exit Program          - Quit the application
8. Temporary Test        - View solution and player grids (debug)
```

### Step-by-Step Workflow

#### 1. **Load Words** (Automatic on startup)
   - Program loads words from `words.txt`
   - Words are stored in both array and Trie structure

#### 2. **Generate Crossword** (Option 3)
   - Selects 15 random words from dictionary
   - Uses backtracking to place words on 12x12 grid
   - Attempts 40 different word orders for best fit
   - Displays generated puzzle on success

#### 3. **Play the Puzzle** (Option 6)
   - Select difficulty level (Easy/Medium/Hard)
   - Initial letters revealed based on difficulty
   - Place letters by entering row, column, and letter
   - Use hints when stuck
   - Complete puzzle to save high score

---

## 🎮 Game Modes

### Difficulty Levels

| Difficulty | Initial Reveal | Random Hints | Word Hints |
|-----------|----------------|--------------|------------|
| **Easy**   | 60% letters    | 10 hints     | 1 per word |
| **Medium** | 50% letters    | 2 hints      | 1 per word |
| **Hard**   | 40% letters    | 4 hints      | 2 per word |

### Gameplay Options

1. **Place a Letter**
   - Enter row (0-11)
   - Enter column (0-11)
   - Enter letter (case-insensitive)
   - Receive immediate feedback

2. **Check Progress**
   - View correct/total letters
   - See completion percentage

3. **Reveal Random Letter** (Hint)
   - Uses one hint credit
   - Reveals any unfilled correct letter
   - Limited based on difficulty

4. **Reveal Word Letter** (Hint)
   - Choose word by number
   - Reveals one letter from that word
   - Limited uses per word

5. **Detailed Progress Report**
   - Comprehensive statistics
   - Letters remaining
   - Completion percentage

6. **Quit to Menu**
   - Save progress and return

### Scoring System
- ✅ **+1 point** for each correct letter
- ❌ **-1 point** for each incorrect letter
- 💔 **Lose 1 life** for incorrect answers
- 🎯 **Game Over** at 0 lives

---

## 🔬 Technical Details

### Data Structures

#### Trie (Prefix Tree)
- **Purpose**: Efficient word storage and retrieval
- **Structure**: 26-child nodes (a-z)
- **Operations**: Insert O(L), Search O(L), where L = word length
- **Features**: Random word selection from entire dictionary

#### 2D Character Arrays
- **Grid**: 12x12 character matrix
- **Solution Grid**: Stores correct answers
- **Player Grid**: Tracks player input

### Algorithms

#### Backtracking for Crossword Generation
```
1. Try to place each word at every position
2. Check horizontal and vertical placements
3. Validate against existing letters
4. Recursively place remaining words
5. Backtrack if placement fails
6. Shuffle word order and retry (up to 40 attempts)
```

#### Word Placement Rules
- No adjacent parallel words (must have 1-cell gap)
- Words can cross at matching letters
- Boundary checking prevents overflow
- Conflict detection prevents letter mismatches

### Key Functions

| Function | Purpose |
|----------|---------|
| `loadWords()` | Load and normalize words from file |
| `generateCrossword()` | Main puzzle generation with shuffling |
| `solveCrossword()` | Recursive backtracking algorithm |
| `canPlaceHorizontal/Vertical()` | Validate word placement |
| `playMode()` | Interactive gameplay loop |
| `revealRandomCell()` | Hint system implementation |
| `isPuzzleSolved()` | Check win condition |

---

## 📄 File Descriptions

### Dictionary Module
- **Dictionary.cpp/h**: Word loading, normalization, and display functions
- **Constants**: MAX_WORDS (100), MAX_LENGTH (20)
- **Features**: File I/O, lowercase conversion, error handling

### Grid Module
- **Grid.cpp/h**: Grid operations and puzzle generation
- **Grid Size**: 12x12 cells
- **Functions**: Initialization, printing, placement validation, backtracking
- **Color Support**: ANSI codes for terminal colors

### Trie Module
- **Trie.cpp/h**: Trie data structure implementation
- **Node Structure**: 26 children + end-of-word flag
- **Operations**: Insert, search, random word selection
- **DFS Collection**: Recursive word gathering

### Main Module
- **main.cpp**: Program entry point and game logic
- **UI Management**: Menu, screen clearing, color output
- **Game State**: Lives, score, hint tracking
- **File Operations**: Save puzzles and high scores

---

## 📦 Dependencies

### Standard Libraries
```cpp
#include <iostream>      // Console I/O
#include <fstream>       // File operations
#include <cstring>       // String manipulation
#include <cstdlib>       // Random numbers, system calls
#include <ctime>         // Time functions
#include <algorithm>     // Shuffling
#include <random>        // Random number generation
#include <limits>        // Input validation
```

### ANSI Color Codes
- Requires terminal with ANSI support
- Windows 10+ (Windows Terminal recommended)
- Linux/Mac (native support)

---

## 🎨 Color Scheme

| Color | Usage |
|-------|-------|
| 🔵 CYAN | Headers, empty cells, information |
| 🟢 GREEN | Success messages, correct letters |
| 🔴 RED | Errors, incorrect letters |
| 🟡 YELLOW | Warnings, prompts |
| 🔷 BLUE | Menu headers |
| 🟣 MAGENTA | Debug information |

---

## 🔮 Future Enhancements

### Potential Features
- [ ] GUI version with graphics library (Qt/SDL)
- [ ] Larger grid sizes (15x15, 20x20)
- [ ] Word categories (animals, countries, etc.)
- [ ] Clue system for words
- [ ] Multiplayer mode
- [ ] Time-based scoring
- [ ] Leaderboard with names
- [ ] Puzzle difficulty rating
- [ ] Export to PDF/image
- [ ] Load saved games
- [ ] Undo/redo functionality
- [ ] Word definition lookup
- [ ] Puzzle solver (hint: show solution)
- [ ] Custom word list import

### Technical Improvements
- [ ] Optimized backtracking algorithm
- [ ] Better word placement heuristics
- [ ] Parallel puzzle generation
- [ ] Database integration for high scores
- [ ] Cross-platform GUI
- [ ] Mobile version

---

## 👨‍💻 Author

**Project**: Crossword Puzzle Generator  
**Language**: C++  
**Course**: Data Structures 
**Developers**: M Uzair Usman & Husnain Shahid

---

## 📝 Notes

### Input Requirements
- Words should be lowercase in `words.txt`
- One word per line
- Maximum 100 words (configurable in Dictionary.h)
- Maximum word length: 20 characters

### Gameplay Tips
- Start with longer words (more hints available)
- Use word hints strategically
- Random hints are precious - save them
- Pay attention to crossing letters
- Check progress regularly

### Troubleshooting

**Issue**: Compilation errors
- **Solution**: Ensure all files are in same directory
- Check for C++11 or higher compiler support

**Issue**: Colors not displaying
- **Solution**: Use Windows Terminal or modern console
- Linux/Mac: No action needed

**Issue**: Crossword generation fails
- **Solution**: Try different word combinations
- Add more words to dictionary
- Reduce number of words (modify line in main.cpp)

**Issue**: File not found
- **Solution**: Ensure `words.txt` is in same directory as executable
- Check file permissions

---

## 📜 License

This project is created for educational purposes.  
Feel free to use and modify for learning and non-commercial purposes.

---

## 🙏 Acknowledgments

- Backtracking algorithm inspiration from classic puzzle solvers
- Trie data structure from DSA coursework
- ANSI color codes from terminal documentation

---

## 📞 Support

For questions or issues:
1. Check the troubleshooting section
2. Review code comments in source files
3. Verify all prerequisites are met

---

**Happy Puzzling! 🧩✨**
