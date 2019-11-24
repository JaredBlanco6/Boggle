#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
Author: Anthony Garcia
Email: anthony2018@my.fit.edu
Course: CSE2010
Section: 2
*/

//assumption of MAP structure
typedef struct map{	
	bool visited;
	char value;
}MAP;

//assumption of TREE structure
typedef struct tree_t{
  //each node has a little that will form a word
  char letter;
  //flag that all the letters make a word, still use 0 and 1
  bool is_word;
  //a single pointer to my parent node
  struct tree_t* parent;
  //pointer to a list of children
  struct tree_t* children;
  //points to the text node in the list
  struct tree_t* next;
}tree_t;

//assumption of Link_word
typedef struct link_word{
	short x,y;
	char letter;
	struct link_word* next;
}Link_word;

typedef struct heap{
	char hello;
}HEAP;

Link_word* initialized_link_word(short x, short y, char value);
tree_t* search_letter(tree_t *dictionary, char value);
void push_letter(Link_word **word, short x, short y, char value);
void pop_letter(Link_word **word);
void DFS(short pos_x, short pos_y, MAP *boggle[], tree_t **dictionary, tree_t *letter_location, HEAP **Heap_word, Link_word **word);


int main(void){

	return 1;
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

void push_letter(Link_word **word, short x, short y, char value){
		Link_word *new_node = initialized_link_word(x, y, value);
		new_node->next = *word;
		*word = new_node;
		if (value == 'Q'){
			Link_word *new_node_2 = initialized_link_word(x, y, 'U');
			new_node_2 = *word;
			*word = new_node_2;
		}
}

Link_word* initialized_link_word(short x, short y, char value){
	Link_word *new_node = (Link_word*)malloc(sizeof(Link_word));
	new_node->x = x;
	new_node->y = y;
	new_node->letter = value;
	new_node->next = NULL;
	return new_node;
}

void pop_letter(Link_word **word){
	if(*word != NULL){
		Link_word *curr_node = *word;
		*word = (*word)->next;
		free(curr_node);
	}
}

//the dfs function should be call in another function since the initial position should be changed
void DFS(short pos_x, short pos_y, MAP *boggle[], tree_t **dictionary, tree_t *letter_location, HEAP **Heap_word, Link_word **word){
	
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
			//insertWord(&(*Heap_word), )
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