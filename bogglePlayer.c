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

#define MAX_SIZE 10
/*
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
*/



//used in the heap





//used map structue in our DFS
typedef struct map{
  bool visited;
  char value;
}MAP;

//assumption of Link_word
typedef struct link_word{
  short x,y;
  char letter;
  struct link_word* next;
}link_word;


bool isFull(WordList);
void insertWord(link_word *, WordList *);
Word createNode(char *, link_word *);
void upHeap(int, WordList *);
void downHeap(WordList *);
int getParent(int );
int leftChildren(int);
int rightChildren(int);
void upHeap(int, WordList*);
int getLength(int, WordList);
void swapMin(char [], WordList *, link_word *);
int getSize(link_word *);
void swap(int, int, WordList *);
void getString(char [], int,link_word *);
//structs for tree
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


/* ------------------------------ */
/* ----- ALL TREE FUNCTIONS ----- */
/* ------------------------------ */

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

/* ------------------------------- */
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

/* ------------------------------ */
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

/* ------------------------------ */
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

/* ------------------------------ */
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

/* ------------------------------ */
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
/* ----- ALL HEAP FUNCTIONS ----- */
/* ------------------------------ */

//Checks if the Heap is full
bool isFull(WordList minHeap){
    //if the next position equals the maximum size of the heap return True for full
    if(minHeap.length == MAX_SIZE){
        return true;
    }
    //otherwise the heap is not full so return false
    else{
        return false;
    }
}


//Creates a node of type NODE and returns it 
Word createNode(char word[], link_word *head){
    Word entry;
    strcpy(entry.word, word);
    entry.path_length = strlen(word);
    int size = entry.path_length;
    link_word *temp = head;

      for(int i =0;i<size;i++){
          if(temp !=NULL){
            entry.path[i].row = temp->x;
            entry.path[i].column = temp->y;
            temp = temp->next;
          }
          else{
            break;
          }
        }



    return entry;
}

//Returns the size of the word by looping through the linked list
int getSize(link_word *head){
  link_word *temp = head;
    int length = 0;
    while(temp != NULL){
        temp = temp->next;
        length++;
    }

    return length;
}

//Creates a string by attaching the characters of the linked list
void getString(char word[], int length, link_word *head){

    link_word *temp = head;
    for(int i = length -1; i>=0; i--){
        word[i] = temp->letter;

        temp = temp->next;

    }
    word[length] = '\0';

}

//this function is called in the DFS everytime we found a valid word
void insertWord(link_word *head , WordList *minHeap){
    //Calls getSize and it assigns it to the size of the word
    int size = getSize(head);
    char word[size];
    //calls the function to get the word from the linked list
    getString(word, size, head);
    // for insertion first checks if the heap is full
    if(isFull(*minHeap)==false){
        int index = (minHeap)->length;
        //the new word is inserted in the heap in the correct position
        (minHeap)->wordlist[index] = createNode(word, head);
        //the new position is updated by addidng one value
        (minHeap)->length = index +1;
        //After the new word is inserted upHeap function is called to sort the heap
        upHeap(index, (minHeap));
    }
    //if the heap is full it checks if current word is larger than the root
    else if(size > minHeap->wordlist[0].path_length){
        //If true then swap with the root
        swapMin(word, minHeap,head);

    }
    else{
      //If the size of the current word is smaller than the root then the word should not be inserted in the heap
      return;

    }

}

//
void upHeap(int index, WordList *minHeap){
    //Calls upheap after inserting the node in the right position
    //It is only called when the heap is not full
    int parent = getParent(index);
    //swap if the parent's word length is greater than itself
    while(index>0 && getLength(parent, *minHeap)>getLength(index,*minHeap)){
        //Calls the swap function which swaps the information at the two indexes
        swap(index,parent,minHeap);
        //after the swap it sets the index to the parent
        index = parent;
        //calls the functino get parent to get the new parent
        parent = getParent(index);
    }

}

void downHeap(WordList *minHeap){
    //downHeap will only be called when the array is full. The insertion is always at the root.
    int index = 0;
    int size = minHeap->length;
    //As long as the children is bigger than the parent and the index is lower than the maximum size of the heap
    while(index<size && leftChildren(index)<size){
        //if the length of the left child is smaller than the length of the inserted word then swap nodes
        if(getLength(index,*minHeap)>getLength(leftChildren(index),*minHeap)){
            //swaps with the left children
            swap(index,leftChildren(index), minHeap);
            //sets the new index to the swapped node
            index = leftChildren(index);
        }
        //if the length of the right child is smaller than the length of the inserted word then swap nodes
        else if (getLength(index, *minHeap)>getLength(rightChildren(index),*minHeap)){
            //if the conditions is true then it swaps with th right child
            swap(index,rightChildren(index), minHeap);
            index = rightChildren(index);
        }
        else{

            break;
        }



    }

}

//This function is called when the heap is full
//It swaps the shortes word in the heap with the new minimum word which will hold a bigger length than the previous Min
void swapMin(char word[], WordList *minHeap, link_word *head){
    //It swaps the new shortes word with the word that was initially at the root
    minHeap->wordlist[0] = createNode(word,head);
    downHeap(minHeap);//Calls down heap to check for the right position of the new inserted word.

}


//get parent index
int getParent(int childIndex){
  return (childIndex - 1) / 2;
}

int leftChildren(int parentIndex){//get left child index
  return 2 * parentIndex + 1;
}


int rightChildren(int parentIndex){//get right child index. return function
  return 2 * parentIndex + 2;
}


int getLength(int index, WordList minHeap){

    int length = minHeap.wordlist[index].path_length;//It stores the length of the word in the heap at the right index
    return length;//returns the length of the word
}


void swap(int index1, int index2, WordList *minHeap){

    Word temp = minHeap->wordlist[index1];
    minHeap->wordlist[index1] = minHeap->wordlist[index2];
    minHeap->wordlist[index2]= temp;


}


/* ------------------------------ */
/* ----- ALL DFS FUNCTIONS ----- */
/* ------------------------------ */
/* ------------------------------ */
link_word* initialized_link_word(short x, short y, char value){
  link_word *new_node = (link_word*)malloc(sizeof(link_word));
  new_node->x = x;
  new_node->y = y;
  new_node->letter = value;
  new_node->next = NULL;
  return new_node;
}

tree_t* search_letter(tree_t *dictionary, char value){
  if (dictionary == NULL)
    return NULL;
  while(dictionary != NULL){
    if (dictionary->letter == value)
      return dictionary;
    else if(dictionary->letter > value)
      return NULL;
    dictionary = dictionary->next;
  }
  return NULL;
}

/* ------------------------------ */
void push_letter(link_word **word, short x, short y, char value){
    link_word *new_node = initialized_link_word(x, y, value);
    new_node->next = *word;
    *word = new_node;
    if (value == 'Q'){
      link_word *new_node_2 = initialized_link_word(x, y, 'U');
      new_node_2 = *word;
      *word = new_node_2;
    }
}


/* ------------------------------ */
void pop_letter(link_word **word){
  if(*word != NULL){
    link_word *curr_node = *word;
    *word = (*word)->next;
    free(curr_node);
  }
}

/* ------------------------------ */
//the dfs function should be call in another function since the initial position should be changed
void DFS(short pos_x, short pos_y, MAP boggle[4][4], tree_t **dictionary, tree_t *letter_location, WordList *Heap_word, link_word **word){

  //saves the position of the letter, the function returns -1 if the letter wasn't found
  letter_location = search_letter((*dictionary)->children, boggle[pos_x][pos_y].value);

  //if the letter was found continue with the DFS
  if (letter_location != NULL){

    //add to the link_word
    push_letter(&(*word), pos_x, pos_y, letter_location->letter);

    //if this is a word (1 for word) then save it in the array
    if (letter_location->is_word == true){
      //save word in the array
      /*
      use a function that calls add_heap (because we want to remove to min word if the heap is full)
      (implement something similar to stack to save the word)
      */
      insertWord(*word, *Heap_word);
      letter_location->is_word = false;
    }

    //sets the letter in the map as already visited
    boggle[pos_x][pos_y].visited = true;

    //checks if the upper position was visited
    if (pos_x-1 > -1 && boggle[pos_x-1][pos_y].visited == false){
      DFS(pos_x-1, pos_y, boggle, &(letter_location), NULL, &(*Heap_word), &(*word));

      //pop a letter from link word
      pop_letter(&(*word));

      //sets this position back to false
      boggle[pos_x-1][pos_y].visited = false;
    }
    //Checks if the lower position was visited
    if (pos_x+1 < 4 && boggle[pos_x+1][pos_y].visited == false){
      DFS(pos_x+1, pos_y, boggle, &(letter_location), NULL, &(*Heap_word), &(*word));

      //pop a letter from link word
      pop_letter(&(*word));

      //sets this position back to false
      boggle[pos_x+1][pos_y].visited = false;
    }
    //checks if the right position was visited
    if (pos_y+1 < 4 && boggle[pos_x][pos_y+1].visited == false){
      DFS(pos_x, pos_y+1, boggle, &(letter_location), NULL, &(*Heap_word), &(*word));

      //pop a letter from link word
      pop_letter(&(*word));

      //sets this position back to false
      boggle[pos_x][pos_y+1].visited = false;
    }
    //checks if the left position was visited
    if (pos_y-1 < -1 && boggle[pos_x][pos_y-1].visited == false){
      DFS(pos_x, pos_y-1, boggle, &(letter_location), NULL, &(*Heap_word), &(*word));

      //pop a letter from link word
      pop_letter(&(*word));

      //sets this position back to false
      boggle[pos_x][pos_y-1].visited = false;
    }
    //Checks if the lower right diagonial position was visited
    if (pos_x+1 < 4 && pos_y+1 < 4 && boggle[pos_x+1][pos_y+1].visited == false){
      DFS(pos_x+1, pos_y+1, boggle, &(letter_location), NULL, &(*Heap_word), &(*word));

      //pop a letter from link word
      pop_letter(&(*word));

      //sets this position back to false
      boggle[pos_x+1][pos_y+1].visited = false;
    }
    //Checks if the lower left diagonial position was visited
    if (pos_x+1 < 4 && pos_y-1 > -1 && boggle[pos_x+1][pos_y-1].visited == false){
      DFS(pos_x+1, pos_y-1, boggle, &(letter_location), NULL, &(*Heap_word), &(*word));

      //pop a letter from link word
      pop_letter(&(*word));

      //sets this position back to false
      boggle[pos_x+1][pos_y-1].visited = false;
    }
    //Checks if the upper left diagonial position was visited
    if (pos_x-1 > -1 && pos_y-1 > -1 && boggle[pos_x-1][pos_y-1].visited == false){
      DFS(pos_x-1, pos_y-1, boggle, &(letter_location), NULL, &(*Heap_word), &(*word));

      //pop a letter from link word
      pop_letter(&(*word));

      //sets this position back to false
      boggle[pos_x-1][pos_y-1].visited = false;
    }
    //Checks if the upper left diagonial position was visited
    if (pos_x-1 > -1 && pos_y+1 < 4 && boggle[pos_x-1][pos_y+1].visited == false){
      DFS(pos_x-1, pos_y-1, boggle, &(letter_location), NULL, &(*Heap_word), &(*word));

      //pop a letter from link word
      pop_letter(&(*word));

      //sets this position back to false
      boggle[pos_x-1][pos_y+1].visited = false;
    }

    //sets the letter in the map as not visited
    boggle[pos_x][pos_y].visited = false;
  }

}






/* ------------------------------ */
/* ---- EVALUATION FUNCTIONS ---- */
/* ------------------------------ */
// initialize BogglePlayer with a file of English words
void initBogglePlayer(char* word_file) {
  //declaring root to dictionary tree
  static tree_t *dictionary_tree = NULL;
  //fills first layer of letter
  decalre_root(&dictionary_tree);


  //scans in our dicitonary and adds all of the letters from words into our tree
  make_tree(word_file, &dictionary_tree); //WE CAN MAKE THIS FASTER BY ADDING A TAIL, MAKE CHILDREN IN ORDER TO SPEED UP DFS


  //free's our tree
  //freeList(&(dictionary_tree));


}



void  sampleWordList(WordList* myWords);   // a sample function to populate a word list

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


tree_t *dictionary_tree = NULL;

WordList* getWords(char board[4][4]) {
	printf("Testing\n");
	tree_t *letter_location = NULL;
	WordList myWords;
	link_word *word = NULL;
	
	MAP bogglemap[4][4];
	for(int i = 0; i < 4; i++){
		for(int j = 0; j<4; j++){
			bogglemap[i][j].value = board[i][j];
			bogglemap[i][j].visited = false;
			printf("%c ", bogglemap[i][j].value);
		}
		printf("\n");
	}
	printf("%p\n", dictionary_tree);
	//printf("LETTER %c\n", dictionary_tree -> children -> next -> next -> letter);
	
	for (int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			DFS(i,j, bogglemap, &dictionary_tree, letter_location, &myWords, &word);
		}
	}
	
	
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
