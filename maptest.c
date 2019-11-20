/*
  Author: Kyle Findley
  Email: kfindley2016@my.fit.edu
  Course: cse2010
  Section: 3

 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include "evalBogglePlayer.h"
#include "bogglePlayer.h"
#include "word.h"


char boggle_dices[16][7] = {"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
                            "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNUQ", "HLNNRZ"};

int main(int argc, char *argv[]){
	printf("Playing Boggle...\n");
	
	int seed = 123456789;
	if (argc == 3) {
        seed = atoi(argv[2]);
    }
    srand(seed);

    // Generate random board, and pass it to bogglePlayer to play Boggle
    char board[4][4];
    int length = 16;

    // Create random board
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int dice_index = rand() % length;
            char* dice = boggle_dices[dice_index];
            board[i][j] = dice[rand() % 6];
            strcpy(boggle_dices[dice_index], boggle_dices[length - 1]);
            strcpy(boggle_dices[length - 1], dice);
            length--;
        }
    }

	for(int i = 0; i < 4; i++){
		for(int j = 0; j< 4; j++){
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}


