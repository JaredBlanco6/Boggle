/*

  Authors (group members):
  Email addresses of group members:
  Group name:

  Course:
  Section:

  Description of the overall algorithm and main data structures:


*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "bogglePlayer.h"
#include "word.h"

/* ----- ALL TREE FUNCTIONS ----- */
typedef struct tree_t{
  //each node has a little that will form a word
  char letter;
  //flag that all the letters make a word, still use 0 and 1
  char is_word;
  //a single pointer to my parent node
  struct tree_t* parent;
  //pointer to a list of children
  struct tree_t* children;
  //points to the text node in the list
  struct tree_t* next;
}tree_t;

//allocates memory for a new node, fills it with given data, and sets everything else to NULL;
tree_t* create_node(char letter, tree_t *parent, int is_word){
  tree_t*new_child = (tree_t*)malloc(sizeof(tree_t));
  new_child->parent = parent;
  new_child->children = NULL;
  new_child->next = NULL;
  new_child->letter = letter;
  new_child->is_word = is_word;

  return new_child;
}

//adds a letter to a linked list
void addNode(tree_t*parent, char new_letter, int is_word){
  //create my node and load it with dat
  tree_t*new_child = create_node(new_letter, parent, is_word);

  //adding our first child
  if(parent->children == NULL){
    parent->children = new_child;
    return;
  }

  tree_t*current_node = parent->children;


  //scroll to the end of the list
  while(current_node->next != NULL){

    //if the letter is already in the list, we don't add the node;
    if(current_node->letter == new_letter){
      //IF we are not going to add this duplicate but the flag is true for antoher word, we take the true flag
      if(current_node->is_word == 0){
        current_node->is_word = is_word; //printf("Flipping flag\n");
      }
      free(new_child);
      return;
    }

    current_node = current_node->next;
  }


  //ensuring no duplicates
  if(current_node->letter == new_letter){
    if(current_node->is_word < is_word){
      current_node->is_word = is_word; //printf("flipping flag %c\n", current_node->letter);
    }
    free(new_child);
    return;
  }


  //adds our new node to our list
  current_node->next = new_child;
}

//looks for a parent and gives them their kid.
//the parent is the first letter, the child is the second letter
void add_children(tree_t**node, char word[],int max_index, int index){
  //error case
  if( (*node) == NULL){
    return;
  }


  //if we reach the point in the word where we would just add a null char to the list
  if((index + 1 > max_index) || (word[index + 1] == '\0')){
    return;
  }


  //if the node and i have the same letter, i add the next letter into the list
  //IE with dog, i look for d, than add o to the d list.
  if((*node)->letter == word[index]){
    //IF we are adding the last letter now
    if(index + 1 == max_index){
      addNode((*node), word[index + 1], 1);
    }else{
      addNode((*node), word[index + 1], 0);
    }
    add_children( &(*node)->children, word, max_index, index +1);

  }else{
    add_children( &(*node)->next, word, max_index, index);
  }
}

//scans in our dictionary and adds all of the individual chars to our tree
void make_tree(char *file_name, tree_t **root){
  //opens the file
  FILE *fin = fopen(file_name, "r");

  //used for scanning and tokenizing
  char temp_input[20];
  short input_length;
  char *token;


  while(fgets(temp_input, 17, fin)){
    input_length = strlen(temp_input);

    //while the last char of temp_input is a non printable char
    while(temp_input[input_length] <= '!'){
      temp_input[input_length] = '\0';
      input_length--;
    }

    add_children( &(*root)->children, temp_input, input_length, 0);
  }
}

//adds our first layer of children to root so the follwoing nodes have a base parent
void decalre_root(tree_t **root){

  *root = create_node(' ', NULL, 0);

  char word[4];
  word[0] = ' '; //it's a space so we add to root
  word[2] = '\0';
  short word_size = 2;

  //makes a base tree of the alphabet
  for(int i = 'A'; i <= 'Z'; i++){
    word[1] = i;
    add_children(&(*root), word, word_size, 0);
  }
}


//recursive way to free my entire tree!
void freeList(tree_t** parent){
  //base case: if we have no list, don't do anything
  if(*parent == NULL){
    return;
  }
  //calls the same function with the next node
  freeList(&(*parent)->next);
  freeList(&(*parent)->children);


  //free's the current node
  free(*parent);
  //fun fact: freeing something does not make it point to NULL but instead just deallcates the memeory and leaves the pointer
  *parent = NULL;
}

/* ------------------------------ */


// initialize BogglePlayer with a file of English words
void initBogglePlayer(char* word_file) {
  //declaring root to dictionary tree
  tree_t *dictionary_tree = NULL;
  //fills first layer of letter
  decalre_root(&dictionary_tree);


  //scans in our dicitonary and adds all of the letters from words into our tree
  make_tree(word_file, &dictionary_tree); //WE CAN MAKE THIS FASTER BY ADDING A TAIL, MAKE CHILDREN IN ORDER TO SPEED UP DFS


  //free's our tree
  freeList(&(dictionary_tree));
}



void      sampleWordList(WordList* myWords);   // a sample function to populate a word list

// based on the board, find valid words
//
// board: 4x4 board, each element is a letter, 'Q' represents "QU",
//    first dimension is row, second dimension is column
//    ie, board[row][col]
//
// Return at most 20 valid words in UPPERCASE and
//    their paths of locations on the board in myWords
//
// See word.h for details of the struct for Word, WordList, Location, and access functions

WordList* getWords(char board[4][4]) {

    WordList* myWords = getNewWordList();

    sampleWordList(myWords);


    return myWords;
}



// a sample list of one word
void sampleWordList(WordList* myWords)  {
    setWordListLength(myWords, 1);      // number of words on the list
    Word *word = getWordFromWordList(myWords, 0);   // first word

    setWord(word, "cat");               // word string

    setPathLength(word, 3);             // word path
    setLetterRowAndCol(word, 0, 1, 2);  // letter 0 is at row 1 and column 2
    setLetterRowAndCol(word, 1, 1, 3);
    setLetterRowAndCol(word, 2, 2, 3);
}
