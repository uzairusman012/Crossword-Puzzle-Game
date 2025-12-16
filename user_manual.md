# 📘 Crossword Puzzle Game - User Manual

**Version 1.0**  
*Complete Guide for Players*

---

## 📑 Table of Contents

1.  [Welcome](#welcome)
2.  [Getting Started](#getting-started)
3.  [Understanding the Interface](#understanding-the-interface)
4.  [Main Menu Guide](#main-menu-guide)
5.  [How to Generate a Puzzle](#how-to-generate-a-puzzle)
6.  [How to Play the Game](#how-to-play-the-game)
7.  [Understanding Difficulty Levels](#understanding-difficulty-levels)
8.  [Using Hints Effectively](#using-hints-effectively)
9.  [Scoring System](#scoring-system)
10. [Tips and Strategies](#tips-and-strategies)
11. [Frequently Asked Questions](#frequently-asked-questions)
12. [Troubleshooting](#troubleshooting)

---

## 🎮 Welcome

Welcome to the **Crossword Puzzle Generator & Game**! This interactive console-based game allows you to:
- Generate unique crossword puzzles automatically
- Play crossword puzzles with multiple difficulty levels
- Track your scores and compete with yourself
- Use smart hints when you get stuck

This manual will guide you through every feature step by step.

---

## 🚀 Getting Started

### Step 1: Launch the Program

**Windows:**
- Double-click on `Crossword.exe` file
- OR open Command Prompt, navigate to folder, type `Crossword` and press Enter

**Linux/Mac:**
- Open Terminal
- Navigate to the program folder
- Type `./Crossword` and press Enter

### Step 2: First Launch

When you start the program, you'll see:
```
Loading words from dictionary...
Words loaded successfully!
```

The program automatically loads all words from the `words.txt` file. You'll then see the main menu.

---

## 🖥️ Understanding the Interface

### Color Coding System

The game uses colors to help you understand what's happening:

| Color | Meaning | Example Use |
|-------|---------|-------------|
| **🔵 Blue (Cyan)** | Information, headers | Menu titles, section headers |
| **🟢 Green** | Success, correct answers | "Correct letter!", successful actions |
| **🔴 Red** | Errors, wrong answers | "Incorrect!", error messages |
| **🟡 Yellow** | Warnings, prompts | Input prompts, warnings |
| **🟣 Magenta** | Special information | Debug mode |

### Grid Display

The crossword grid looks like this:

```
   0 1 2 3 4 5 6 7 8 9 10 11
0: _ _ c a t _ _ _ _ _ _ _
1: _ _ a _ _ _ _ _ _ _ _ _
2: _ _ r _ _ _ _ _ _ _ _ _
3: d o g _ _ _ _ _ _ _ _ _
```

- **Numbers on top (0-11)**: Column numbers
- **Numbers on left (0-11)**: Row numbers
- **Underscore (_)**: Empty cell or hidden letter
- **Letters**: Revealed or placed letters

---

## 📋 Main Menu Guide

When you start the program, you'll see this menu:

```
================== CROSSWORD MENU ==================
1. Show Word List
2. Shuffle Words
3. Generate Crossword
4. Display Crossword Grid
5. Save Crossword to File
6. Play Crossword
7. Exit Program
8. Temporary Test
====================================================
```

### Option Descriptions

#### 1️⃣ Show Word List
- **What it does**: Displays all words loaded from the dictionary
- **When to use**: Check what words are available for puzzles
- **Output**: Numbered list of all words

**Example:**
```
Loaded Words: 100
1. cat
2. dog
3. sun
...
```

#### 2️⃣ Shuffle Words
- **What it does**: Randomizes the order of words
- **When to use**: Before generating a puzzle for variety
- **Note**: This doesn't generate a puzzle, just changes word order

#### 3️⃣ Generate Crossword ⭐ (Most Important)
- **What it does**: Creates a new crossword puzzle automatically
- **Process**: 
  - Picks 15 random words from dictionary
  - Uses smart algorithm to arrange them on grid
  - May take a few seconds
- **Output**: Displays the generated puzzle

**Success Message:**
```
Generating crossword using backtracking...
Crossword Successfully Generated!
```

**Note**: This must be done before you can play!

#### 4️⃣ Display Crossword Grid
- **What it does**: Shows the current puzzle
- **When to use**: View puzzle after generating
- **Note**: Won't work if no puzzle is generated yet

#### 5️⃣ Save Crossword to File
- **What it does**: Saves puzzle to `puzzle.txt` file
- **Contents**: Grid layout + word list
- **Location**: Same folder as program
- **Use case**: Print puzzle to solve on paper

#### 6️⃣ Play Crossword ⭐ (Game Mode)
- **What it does**: Starts interactive gameplay
- **Requirements**: Must generate puzzle first (Option 3)
- **See Section**: [How to Play the Game](#how-to-play-the-game)

#### 7️⃣ Exit Program
- **What it does**: Closes the application
- **Note**: Your high scores are saved automatically

#### 8️⃣ Temporary Test
- **What it does**: Shows both solution and player grids (for debugging)
- **Use**: Check if puzzle generated correctly

---

## 🎯 How to Generate a Puzzle

### Step-by-Step Tutorial

**Step 1:** From main menu, type `3` and press Enter
```
Enter choice: 3
```

**Step 2:** Wait for generation process
```
Generating crossword using backtracking...
(This may take a few seconds...)
```

**Step 3:** See your puzzle!
```
Crossword Successfully Generated!

   0 1 2 3 4 5 6 7 8 9 10 11
0: _ _ _ c a t _ _ _ _ _ _
1: _ _ _ o _ _ _ _ _ _ _ _
2: d o g _ _ _ _ _ _ _ _ _
...
```

**Step 4:** Press Enter to return to menu

### What If Generation Fails?

If you see:
```
Failed to generate crossword.
```

**Don't worry!** Just:
1. Press Enter to return to menu
2. Try Option 3 again
3. The program will try different word combinations
4. Usually succeeds within 1-3 attempts

**Why it happens**: Sometimes words don't fit together well. The program automatically tries 40 different arrangements.

---

## 🎮 How to Play the Game

### Starting a Game

**Prerequisites:**
- Must have generated a puzzle (Option 3)

**Steps:**

1. From main menu, select Option 6 (Play Crossword)
```
Enter choice: 6
```

2. Choose your difficulty level:
```
Select Difficulty Level:
1. Easy (60% letters revealed)
2. Medium (50% letters revealed)
3. Hard (40% letters revealed)
Enter choice: 
```

3. Type `1`, `2`, or `3` and press Enter

### Game Screen Layout

```
=========== PLAYER MODE ===========
Lives: 3   |   Score: 0   |   Random Hints Left: 10
====================================

Your Puzzle:
   0 1 2 3 4 5 6 7 8 9 10 11
0: _ _ _ c a t _ _ _ _ _ _
1: _ _ _ o _ _ _ _ _ _ _ _
2: d o g _ _ _ _ _ _ _ _ _

Options:
1. Place a letter
2. Check progress
3. Reveal a random correct letter (Hint)
4. Reveal a letter from a specific word
5. Detailed progress report
6. Quit to main menu
Enter choice: 
```

### Color-Coded Cells

During gameplay, cells are colored:
- **🔵 Cyan (Empty cells)**: Not filled yet
- **🟢 Green letters**: Correct letters you placed
- **🔴 Red letters**: Incorrect letters you placed

---

## 🎯 Gameplay Actions

### 1. Place a Letter (Main Action)

**Steps:**

1. Select Option 1
```
Enter choice: 1
```

2. Enter row number (0-11)
```
Enter row (0–11): 2
```

3. Enter column number (0-11)
```
Enter column (0–11): 3
```

4. Enter your letter (any case)
```
Enter letter: o
```

5. Get instant feedback:

**If Correct:**
```
✓ Correct!
[Score increases by 1]
Press Enter to continue...
```

**If Incorrect:**
```
✗ Incorrect!
[Score decreases by 1]
[Lose 1 life]
Lives left: 2
Press Enter to continue...
```

**Pro Tips:**
- Letters can be uppercase or lowercase (both work)
- You can only place letters in cells that are part of words
- Empty spaces (not part of any word) cannot be filled

### 2. Check Progress

Shows quick summary:
```
Progress: 25 / 48
```
- 25 = correct letters placed
- 48 = total letters in puzzle

### 3. Reveal Random Letter (Hint)

**What it does:** 
- Reveals one random correct letter anywhere in puzzle
- Uses one hint credit

**How to use:**
1. Select Option 3
2. Program automatically reveals a letter
```
A random letter has been revealed!
```

**Limits:**
- Easy: 10 random hints
- Medium: 2 random hints  
- Hard: 4 random hints

### 4. Reveal Letter from Specific Word

**What it does:**
- Reveals one letter from a word you choose
- Helpful when stuck on a specific word

**How to use:**

1. Select Option 4
2. Look at word list (displayed at start)
3. Enter word number:
```
Enter word number (1–15): 3
```
4. One letter from that word gets revealed
```
One letter from "dog" has been revealed!
```

**Limits:**
- Easy/Medium: 1 hint per word
- Hard: 2 hints per word
- Once limit reached: "You already used a hint for this word"

### 5. Detailed Progress Report

Shows comprehensive statistics:
```
===== PROGRESS REPORT =====
Correct letters: 30/48
Letters remaining: 18
Completion: 62.5%
```

### 6. Quit to Main Menu

Exits game and returns to main menu (progress is lost).

---

## 📊 Understanding Difficulty Levels

### Easy Mode 🟢
**Best for: Beginners**

| Feature | Value |
|---------|-------|
| Initial letters revealed | 60% |
| Random hints available | 10 |
| Word hints per word | 1 |
| Lives | 3 |

**When to choose**: First time playing, learning the game, or relaxed play

### Medium Mode 🟡
**Best for: Regular players**

| Feature | Value |
|---------|-------|
| Initial letters revealed | 50% |
| Random hints available | 2 |
| Word hints per word | 1 |
| Lives | 3 |

**When to choose**: You understand the game and want moderate challenge

### Hard Mode 🔴
**Best for: Experts**

| Feature | Value |
|---------|-------|
| Initial letters revealed | 40% |
| Random hints available | 4 |
| Word hints per word | 2 |
| Lives | 3 |

**When to choose**: You want maximum challenge and high scores

---

## 💡 Using Hints Effectively

### Hint Strategy Guide

#### When to Use Random Hints 🎲
- ✅ **Good times:**
  - Stuck on multiple words
  - Need general progress
  - Early in game to reveal crossing letters
  
- ❌ **Avoid:**
  - When you know most letters
  - On easy mode (you have many, but still limited)
  - Last resort only

#### When to Use Word Hints 📝
- ✅ **Good times:**
  - Stuck on one specific long word
  - Word with uncommon letters
  - Strategic: choose words that cross other words
  
- ❌ **Avoid:**
  - Short words you can guess
  - When random hint is better
  - After already using hint on that word

### Advanced Hint Tactics

**Tactic 1: Cross-Word Strategy**
- Use word hints on words that cross many other words
- One revealed letter can help with 2 words at once!

**Tactic 2: Save Hints for Hard Parts**
- Try guessing common letters first (e, a, t, o, n)
- Use hints only when really stuck

**Tactic 3: Pattern Recognition**
- If you see `_a_`, think of 3-letter words
- If you see `___e`, think of words ending in 'e'
- Use hints to confirm your guesses

---

## 🏆 Scoring System

### How Points Work

**Earning Points:**
- ✅ Each correct letter = **+1 point**

**Losing Points:**
- ❌ Each incorrect letter = **-1 point**
- ❌ Each incorrect letter = **-1 life**

**Lives:**
- You start with **3 lives**
- Game over at **0 lives**

### Score Examples

**Example 1: Perfect Game**
- Total letters: 48
- All correct: +48 points
- No mistakes: No penalties
- **Final Score: 48 points**

**Example 2: Few Mistakes**
- Correct letters: 45 (+45)
- Wrong attempts: 5 (-5)
- **Final Score: 40 points**

**Example 3: Many Mistakes**
- Correct letters: 30 (+30)
- Wrong attempts: 10 (-10)
- **Final Score: 20 points**
- Lives: Lost 3 lives = Game Over at 10th mistake

### High Score System

**Automatic Saving:**
- Scores saved when you complete puzzle
- Saved to `highscores.txt` file
- Includes date of completion

**Viewing High Scores:**
- Open `highscores.txt` in notepad
- Format: `[Score] [Date]`

**Example:**
```
48 2024-12-16
35 2024-12-15
42 2024-12-14
```

---

## 🎯 Tips and Strategies

### For Beginners

1. **Start with Easy Mode**
   - Get familiar with controls
   - Learn the grid system
   - Understand color coding

2. **Look for Short Words First**
   - 3-letter words: cat, dog, sun
   - Easier to complete
   - Give you crossing letters

3. **Use Crossing Letters**
   - When two words share a letter
   - One correct guess helps both words
   - Look for intersections

4. **Save Hints**
   - Don't use all hints immediately
   - Keep some for difficult parts
   - Use when lives are low

### For Advanced Players

1. **Pattern Matching**
   - Common endings: -ing, -ed, -er
   - Common beginnings: un-, re-, pre-
   - Vowel patterns: e_e, a_e, o_e

2. **Strategic Guessing**
   - Most common letters: e, t, a, o, i, n
   - Try these first in unclear positions
   - Fewer wrong guesses = higher score

3. **Word Length Analysis**
   - Count underscores to know word length
   - Eliminate impossible words from list
   - Match length to word list

4. **Hint Optimization**
   - Use word hints on longest words
   - These often cross multiple words
   - Maximum benefit per hint

### Score Maximization

**To get highest scores:**
- ✅ Minimize wrong guesses
- ✅ Complete puzzle with all 3 lives
- ✅ Use hints strategically, not frequently
- ✅ Think before placing each letter
- ✅ Check progress regularly

---

## ❓ Frequently Asked Questions

### General Questions

**Q: Can I add my own words to the dictionary?**  
A: Yes! Open `words.txt` in Notepad and add words (one per line, lowercase). Save and restart program.

**Q: How many words are in each puzzle?**  
A: Exactly 15 words are randomly selected for each puzzle.

**Q: Can I play the same puzzle again?**  
A: Generate a new puzzle after completing one. Each generation creates different puzzle.

**Q: Are puzzles saved automatically?**  
A: No, use Option 5 (Save to File) to manually save a puzzle.

**Q: What's the grid size?**  
A: 12 rows × 12 columns (144 cells total).

### Gameplay Questions

**Q: I placed a letter in the wrong spot. Can I undo?**  
A: No undo feature currently. The letter remains until game ends.

**Q: Why can't I place a letter in some cells?**  
A: Empty cells (not part of any word) cannot be filled. Only cells with letters in solution are playable.

**Q: Do capital letters matter?**  
A: No, both UPPER and lower case work the same.

**Q: Can I see the solution?**  
A: Solution shown only when:
- You run out of lives (Game Over)
- You complete the puzzle (Victory)

**Q: What happens if I run out of hints?**  
A: You must solve remaining letters without hints. Plan hint usage carefully!

**Q: Can I pause the game?**  
A: No pause feature. You can quit to menu (Option 6), but progress is lost.

### Technical Questions

**Q: Why aren't colors showing?**  
A: 
- Windows: Use Windows Terminal or Windows 10+
- Older CMD may not support colors
- Linux/Mac: Should work by default

**Q: Program says "cannot open file words.txt"**  
A: Ensure `words.txt` is in the same folder as the program executable.

**Q: Crossword generation keeps failing**  
A: 
- Try again 2-3 times
- Check if `words.txt` has enough words (minimum 20+)
- Ensure words are lowercase

**Q: High scores not saving**  
A: Check if program has write permissions in its folder.

---

## 🔧 Troubleshooting

### Problem: Program won't start

**Possible Causes:**
- Missing files
- Wrong folder

**Solutions:**
1. Check all files are present (especially `words.txt`)
2. Open Command Prompt/Terminal in correct folder
3. Try running as administrator (Windows)

### Problem: "Error: cannot open file words.txt"

**Solutions:**
1. Verify `words.txt` exists in program folder
2. Check file name spelling (case-sensitive on Linux)
3. Ensure file has read permissions
4. Try recreating the file

### Problem: Crossword generation always fails

**Solutions:**
1. Click Option 3 again (try 2-3 times)
2. Check words.txt has at least 20-30 words
3. Ensure words are all lowercase
4. Remove very long words (over 12 letters)
5. Make sure each word is on separate line

### Problem: Colors not displaying correctly

**Solutions:**

**Windows:**
- Use Windows Terminal (recommended)
- Update to Windows 10 or higher
- Or: Colors appear as codes like `[36m` - still playable

**Linux/Mac:**
- Should work automatically
- Try different terminal if needed

### Problem: Can't place letters

**Possible Causes:**
- Trying to fill empty cell (not part of puzzle)
- No puzzle generated yet

**Solutions:**
1. Ensure puzzle is generated (Option 3)
2. Only fill cells that have letters in solution
3. Check row/column numbers are correct (0-11)

### Problem: Input not working

**Solutions:**
1. Make sure to press Enter after typing
2. Enter only valid numbers/letters
3. If stuck: press Ctrl+C to quit, restart program

### Problem: Score not saving

**Solutions:**
1. Complete the puzzle (don't quit mid-game)
2. Check folder permissions
3. Look for `highscores.txt` in program folder
4. If missing, program should create it automatically

---

## 📞 Quick Reference Card

### Essential Controls

| Action | Keys |
|--------|------|
| Select menu option | Type number + Enter |
| Place letter | Row + Column + Letter + Enter |
| Continue | Press Enter |
| Exit program | Choose option 7 |
| Force quit | Ctrl + C (emergency only) |

### Grid Coordinates

```
Column →
Row ↓    0  1  2  3  4  5...
    0    _  _  c  a  t  _
    1    _  _  a  _  _  _
    2    _  _  r  _  _  _
    3    d  o  g  _  _  _
```

Example: To fill (0,2) with 'c': Enter row=0, col=2, letter=c

### Quick Start Workflow

1. Launch program ▶
2. Option 3 (Generate) ▶
3. Option 6 (Play) ▶
4. Choose difficulty ▶
5. Start playing! ▶
6. Complete puzzle ▶
7. Check high scores

---

## 📚 Word List Information

### Default Dictionary

The game includes **100 common words** in these categories:
- Animals (cat, dog)
- Nature (sun, moon, tree)
- School (book, pen, teacher)
- Transport (car, bus, train)
- Food (bread, rice, fruit)
- Home (house, room, door)
- Technology (computer, phone, internet)
- Colors (blue, green, red)
- And more!

### Custom Words

**To add your own words:**

1. Open `words.txt` in Notepad/Text Editor
2. Add one word per line
3. Use lowercase letters only
4. Save file
5. Restart program

**Example words.txt:**
```
cat
dog
elephant
computer
programming
algorithm
```

**Rules:**
- Maximum 100 words total
- Maximum 20 characters per word
- Only letters (a-z)
- No spaces, numbers, or special characters

---

## 🎓 Learning Resources

### Understanding the Grid

The 12×12 grid has:
- **144 total cells**
- **Numbered 0-11** (both rows and columns)
- Words placed **horizontally** (left to right)
- Words placed **vertically** (top to bottom)
- Words can **cross** at matching letters

### Game Concepts

**Crossword Basics:**
- Words intersect at common letters
- No adjacent words without crossing
- All words from your dictionary
- Letters must match at intersections

**Strategy Concepts:**
- **Crossing letters**: One letter in two words
- **Completion percentage**: How close to winning
- **Hint economy**: Using hints wisely
- **Score optimization**: Fewer mistakes = higher score

---

## 🏁 Conclusion

Congratulations! You now know everything about playing the Crossword Puzzle Game.

### Remember:
- 🎯 Practice makes perfect
- 💡 Use hints strategically
- 🏆 Try beating your high scores
- 📚 Add custom words for variety
- 🎮 Experiment with different difficulties

**Have fun and happy puzzling!** 🧩✨

---

## 📄 Document Information

**Manual Version:** 1.0  
**Last Updated:** December 2024  
**For Program Version:** Crossword Puzzle Generator v1.0

---

**Need more help?** Review this manual or check the README.md file for technical details.

**Enjoy the game! 🎉**
