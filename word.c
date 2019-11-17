/* 
   *************************************************************
   *** Do NOT change the existing functions
   *** However, you may add additional functions
   **************************************************************

   Author: Jesse Torres and Philip Chan  
   Email: jtorres2015@my.fit.edu, pkc@cs.fit.edu

   Implementation of functions for manipuating Word and WordList

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "word.h"

//******** functions for manipuating Word, which has string and path  *******

// Copy given string into word
void setWord(Word* w , char* myString) {
  strncpy(w->word, myString, MAX_WORD_LEN + 1);
}

// Copy input path into word path
void setPath(Word* w , int path_length, Location path[path_length]) {
  if (path_length > MAX_WORD_LEN)  
    path_length = MAX_WORD_LEN;  // only up to MAX_WORD_LEN locations are valid
  else if (path_length < 0)
    path_length = 0;

  for (int i = 0; i < path_length; i++) {
    w->path[i].row = path[i].row;
    w->path[i].column = path[i].column;
  }
  w->path_length = path_length;
}

// Set the path length of a word
void setPathLength(Word* w, int path_length) {
  if (path_length > MAX_WORD_LEN)
    {
      path_length = MAX_WORD_LEN;  // only up to MAX_WORD_LEN locations are valid
      printf("setPathLength(): path_length %d exceeds MAX_WORD_LEN", path_length); 
    }
  else if (path_length < 0)
    {
      path_length = 0;
      printf("setPathLength(): path_length %d should not be negative", path_length); 
    }

  w->path_length = path_length; 
}

// return true if row and col are valid
bool validRowCol(int row, int col)
{
  if ((row >= 0) && (row <= 3) && (col >= 0) && (col <= 3))
    return true;
  else
    {
      printf("validRowCol(): invalid row %d or column %d\n", row, col);
      return false;	
    }
}
  

// Set the row and column of a letter at letter_index on the path
void setLetterRowAndCol(Word* w , int letter_index, int row, int col) {
  if ((letter_index >= 0) && (letter_index < w->path_length) &&
      validRowCol(row, col)) {
    w->path[letter_index].row = row;
    w->path[letter_index].column = col;
  } else {
    printf("setLetterRowAndCol(): invalid letter_index %d, path_length is %d\n", letter_index, w->path_length); 
  }
  
}

// Add a row and column of a letter on the path
void addLetterRowAndCol(Word* w , int row, int col) {
  if ((w->path_length < MAX_WORD_LEN) &&  // only up MAX_WORD_LEN locations are valid
      validRowCol(row, col)) {
    w->path[w->path_length].row = row;
    w->path[w->path_length].column = col;
    w->path_length++;
  } else {
    printf("addLetterRowAndCol(): current path_length %d has reached capacity\n", w->path_length);
  }
}


// ***** functions for manipulating WordList ******* 


// set valid number of words for the word list
void setWordListLength(WordList *wordlist, int len)
{
  if (len > MAX_WORDLIST_LEN)
    {
      len = MAX_WORDLIST_LEN;
      printf("setWordListLength(): len %d exceeds MAX_WORDLIST_LEN \n", len);
    }
  else if (len < 0)
    {
      len = 0;
      printf("setWordListLength(): len %d should not be negative\n", len);
    }
  
  wordlist->length = len;
}

// get a word struct at index from the word list
Word* getWordFromWordList(WordList *myWords, int index)
{
  if ((index >= 0) && (index < myWords->length))
    {
      return &(myWords->wordlist[index]);
    }
  else
    {
      printf("getWord(): invalid index %d, length is %d\n", index, myWords->length);
      return NULL;
    }
}

// create and return a new empty word list
WordList* getNewWordList()
{
    WordList* myWords = (WordList*) malloc(sizeof(WordList));  // allocate a word list
    bzero((void*) myWords, sizeof(WordList));                  // initialize to all zeros

    return myWords;
}
