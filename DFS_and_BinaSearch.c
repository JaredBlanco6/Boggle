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


*tree_t search_letter(tree_t *dictionary, char value){
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

//the dfs function should be call in another function since the initial position should be changed
void DFS(short pos_x, short pos_y, MAP *boggle[], tree_t **dictionary, tree_t *letter_location){
	
	//saves the position of the letter, the function returns -1 if the letter wasn't found
	letter_location = search_letter((*dictionary)->children, boggle[pos_x][pos_y]);
	
	//if the letter was found continue with the DFS
	if (letter_location != NULL){
		
		//if this is a word (1 for word) then save it in the array
		if (letter_location->is_word == true){
			//save word in the array
			/*
			use a function that calls add_heap (because we want to remove to min word if the heap is full)
			(implement something similar to stack to save the word)
			*/
			letter_location->is_word = false;
		}
		
		//sets the letter in the map as already visited
		boggle[pos_x][pos_y].visited = true;

		//checks if the upper position was visited
		if (pos_x-1 > -1 && boggle[pos_x-1][pos_y].visited == false){
			DFS(pos_x-1, pos_y, boggle, &(letter_location), NULL);
			//sets this position back to false
			boggle[pos_x-1][pos_y].visited = false;
		}
		//Checks if the lower position was visited
		if (pos_x+1 < 4 && boggle[pos_x+1][pos_y].visited == false){
			DFS(pos_x+1, pos_y, boggle, &(letter_location), NULL);
			//sets this position back to false
			boggle[pos_x+1][pos_y].visited = false;
		}
		//checks if the right position was visited
		if (pos_y+1 < 4 && boggle[pos_x][pos_y+1].visited == false){
			DFS(pos_x, pos_y+1, boggle, &(letter_location), NULL);
			//sets this position back to false
			boggle[pos_x][pos_y+1].visited = false;
		}
		//checks if the left position was visited
		if (pos_y-1 < -1 && boggle[pos_x][pos_y-1].visited == false){
			DFS(pos_x, pos_y-1, boggle, &(letter_location), NULL);
			//sets this position back to false
			boggle[pos_x][pos_y-1].visited = false;
		}
	}
	
}