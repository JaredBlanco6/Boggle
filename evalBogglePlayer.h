/**********************************************************
 * Uncomment the operating system that you ARE using and
 * comment out the operating systems that you are NOT using
 **********************************************************/

#define LINUX // code01.fit.edu, where your submission will be evaluated
//#define MAC_OS
//#define WINDOWS
//#define OTHERS


/*
   Compilation instructions

   LINUX, MAC_OS, OTHERS:
   gcc -o evalBogglePlayer evalBogglePlayer.c bogglePlayer.c word.c -lm

   or equivalently,

   gcc -o evalBogglePlayer *.c -lm

   as long as the three files above are the only .c files in your working directory

   WINDOWS:
   gcc -o evalBogglePlayer evalBogglePlayer.c bogglePlayer.c word.c -lm -lpsapi

   or 

   gcc -o evalBogglePlayer *.c -lm -lpsapi
*/
