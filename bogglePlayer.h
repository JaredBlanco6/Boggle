/*

    DO NOT MODIFY THIS FILE

    This is the interface of functions provided by the bogglePlayer module
    for the other modules.

    Internal bogglePlayer functions not intended for other modules are
    NOT declared here.

 */

#ifndef BOGGLE_PLAYER_H
#define BOGGLE_PLAYER_H

#include "word.h"

void initBogglePlayer(char* word_file);

WordList* getWords(char board[4][4]);

#endif
