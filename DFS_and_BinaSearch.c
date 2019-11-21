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
typedef struct tree{	
	bool word;
	char value;
	short size;
	struct tree *children;
	struct tree *parent;
}TREE;


int binary_search(TREE *dictionary, char value, int max, int min){
	//the mid value between max(bound) and min(bound)
	int mid = (max+min)/2;
	//return mid if the value has found at that position
	if (dictionary->children[mid].value == value)
		return mid;
	else{
		//return error if the value was not found and all possible positions were checked
		if (max < min)
			return -1;
		//if the mid(value) is bigger then the wanted value then change the max(bound)
		else if(dictionary->children[mid].value > value)
			return binary_search(dictionary, value, mid-1, min);
		//if the mid(value) is smaller then the wanted value then change the min(bound)
		else
			return binary_search(dictionary, value, max, mid+1);
	}
}

//the dfs function should be call in another function since the initial position should be changed
void DFS(short pos_x, short pos_y, MAP *boggle[], TREE **dictionary){
	
	//saves the position of the letter, the function returns -1 if the letter wasn't found
	short letter_location = binary_search(*dictionary, boggle[pos_x][pos_y].value, (*dictionary)->size, 0);
	
	//if the letter was found continue with the DFS
	if (letter_location != -1){
		
		//saves the address of the letter in the dictionary
		TREE *letter_pointer = &((*dictionary)->children[letter_location]);
		
		//if this is a word (1 for word) then save it in the array
		if (letter_pointer->word == true){
			//save word in the array
			/*
			use a function that calls add_heap (because we want to remove to min word if the heap is full)
			(implement something similar to stack to save the word)
			*/
			letter_pointer->word = false;
		}
		
		//sets the letter in the map as already visited
		boggle[pos_x][pos_y].visited = true;

		//checks if the upper position was visited
		if (pos_x-1 > -1 && boggle[pos_x-1][pos_y].visited == false){
			DFS(pos_x-1, pos_y, boggle, &(letter_pointer));
			//sets this position back to false
			boggle[pos_x-1][pos_y].visited = false;
		}
		//Checks if the lower position was visited
		if (pos_x+1 < 4 && boggle[pos_x+1][pos_y].visited == false){
			DFS(pos_x+1, pos_y, boggle, &(letter_pointer));
			//sets this position back to false
			boggle[pos_x+1][pos_y].visited = false;
		}
		//checks if the right position was visited
		if (pos_y+1 < 4 && boggle[pos_x][pos_y+1].visited == false){
			DFS(pos_x, pos_y+1, boggle, &(letter_pointer));
			//sets this position back to false
			boggle[pos_x][pos_y+1].visited = false;
		}
		//checks if the left position was visited
		if (pos_y-1 < -1 && boggle[pos_x][pos_y-1].visited == false){
			DFS(pos_x, pos_y-1, boggle, &(letter_pointer));
			//sets this position back to false
			boggle[pos_x][pos_y-1].visited = false;
		}
	}
	
}