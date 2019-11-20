#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char word[16];//string
    
}Qpatients;



void wordInsert(char *, );//priority queue 
Qpatients patRemoveMin(pQueue *argPQ); 


int main (void){
    

   



    return 0;
}

void wordInsert(char *, Qpatients entry){//priority queue 

  short int length;//insert at the end of the array
  argPQ->patients[size] = entry;
  argPQ->patientsCount++;//increment the count
  
  patupheap(argPQ, size);//up heap starting from the last index
}


Qpatients patRemoveMin(pQueue *argPQ){
    Qpatients *temp = argPQ->patients[0];
    int size = argPQ->patientsCount;
    argPQ->patients[0] = argPQ->patients[size-1];
    patdownheap(argPQ);
    return temp;

} 
 