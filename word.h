/** You may add additional functions, but may not change existing functions
  *
  * The word struct has two components:
  *
  * the word (string)
  * path: the location on the board for each consecutive letter of the word (array of locations)
  *
  * Note that for words that contain "QU", the length of a word is longer
  * than its path by 1 since "QU" in a word is represented by "Q" on the board
  *
  */

#ifndef WORD_H
#define WORD_H

#define MAX_WORD_LEN 16      // 4x4 board, at most 16 letters
#define MAX_WORDLIST_LEN 20  // maximum 20 words

// location of a letter
typedef struct location {
  int    row;                      // 0 to 3
  int    column;                   // 0 to 3
} Location;

// word has the string and path
typedef struct word {
  char     word[MAX_WORD_LEN + 1];  // terminated with '\0'
  Location path[MAX_WORD_LEN];      // path of the letters in the word
  int      path_length;             // actual number of letters/locations in the path
} Word;

// a list of words
typedef struct wordList {
  Word     wordlist[MAX_WORDLIST_LEN];   // at most 20 words
  int      length;                       // actual number of words
} WordList;


// Copy given string into word
void setWord(Word* w, char* myWord);

// Copy input path into word path
void setPath(Word* w, int path_length, Location path[path_length]);

// Set the path length of a word
void setPathLength(Word* w, int path_length);

// Set the row and column of a letter at letter_index on the path
void setLetterRowAndCol(Word* w, int letter_index, int row, int col);

// Add a row and column of a letter on the path
void addLetterRowAndCol(Word* w, int row, int col);

// set valid number of words for the word list
void setWordListLength(WordList *wordlist, int len);

// get a word struct at index from the word list
Word* getWordFromWordList(WordList *wordlist, int index);

// get a new empty word list
WordList* getNewWordList();                    


#endif
