#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


#define MAX_SIZE 20

typedef struct word{
    char word[18];
    int length;
    int path[16][2]; 

}NODE;


typedef struct index{

    NODE wordHeap[MAX_SIZE];
    int position; // The position where you have to insert the next word 
}HEAP;




bool isFull(HEAP);
void insertWord(link_word *, HEAP *);
NODE createNode(char *);
void upHeap(int, HEAP *);
void downHeap(HEAP *);
int getParent(int );
int leftChildren(int);
int rightChildren(int);
void upHeap(int, HEAP*);
int getLength(int, HEAP);
void swapMin(char [], HEAP *);
void swap(int, int, HEAP *);
int getLength (link_word *);
char* getString(int,link_word *);



int main (void){

    HEAP minHeap;
    minHeap.position = 0;
    int index = 0 ;
    
    
    
    
    
    insertWord("1",&minHeap);
    insertWord("12",&minHeap);
    insertWord("123",&minHeap);
    insertWord("1234",&minHeap);
    insertWord("12345",&minHeap);
    insertWord("1",&minHeap);
    insertWord("12",&minHeap);
    insertWord("123",&minHeap);
     insertWord("1234",&minHeap);
    insertWord("12345",&minHeap);
    insertWord("1",&minHeap);
    insertWord("12",&minHeap);
    insertWord("123",&minHeap);
    insertWord("1234",&minHeap);
    insertWord("12345",&minHeap);
    insertWord("1",&minHeap);
    insertWord("12",&minHeap);
    insertWord("123",&minHeap);
     insertWord("1234",&minHeap);
    insertWord("12345",&minHeap);
    insertWord("1",&minHeap);
    insertWord("12",&minHeap);
    insertWord("123",&minHeap);
     insertWord("1234",&minHeap);
    insertWord("12345",&minHeap);
    insertWord("1",&minHeap);
    insertWord("12",&minHeap);
    insertWord("123",&minHeap);
     insertWord("1234",&minHeap);
    insertWord("12345",&minHeap);
    insertWord("1",&minHeap);
  
   
    
    

    printf("List : ");
    for(int i=0;i<minHeap.position;i++){
        printf("%s ", minHeap.wordHeap[i].word);
    }

    return 0;

}

bool isFull(HEAP minHeap){

    if(minHeap.position == MAX_SIZE){
        return true;
    }
    else{
        return false;
    }
}

void insertWord(link_word *head , HEAP **minHeap){

    int size = getLength(head);
    char word[size] = getString(size, head);

    if(isFull(*minHeap)==false){
        int index = (*minHeap)->position;
        *minHeap->wordHeap[index] = createNode(word);
        *minHeap->position = index +1;
        upHeap(index, *minHeap);
    }
    else{
        swapMin(word, *minHeap);
    }
     
}


int getLength (link_word *head){
    int length = 0;
    while(temp != NULL){
        temp = temp->next;
        length++;
    }

    return length;
}


char* getString(int length, link_word *head){

    link_word *temp = *head;
    for(int i = length -1; i>=0; i--){
        word[i] = temp->letter;
        temp = temp->next;

    }

    return word;

    

NODE createNode(char word[]){
    NODE entry;
    strcpy(entry.word, word);
    entry.length = strlen(word);
    return entry;
}

void upHeap(int index, HEAP *minHeap){
    int parent = getParent(index); 
    while(index>0 && getLength(parent, *minHeap)>getLength(index,*minHeap)){
        swap(index,parent,minHeap);
        index = parent;
        parent = getParent(index);    
    }

}

void downHeap(HEAP *minHeap){
    //downHeap will only be called when the array is full. The insertion is always at the root.
    int index = 0;
    int size = minHeap->position;

    while(index<size && leftChildren(index)<size){
        if(getLength(index,*minHeap)>getLength(leftChildren(index),*minHeap)){
            swap(index,leftChildren(index), minHeap);
            index = leftChildren(index);
        }
        else if (getLength(index, *minHeap)>getLength(rightChildren(index),*minHeap)){
            swap(index,rightChildren(index), minHeap);
            index = rightChildren(index);
        }
        else{

            break;
        }

      

    }

}

void swapMin(char word[], HEAP *minHeap){
    
    minHeap->wordHeap[0] = createNode(word);
    downHeap(minHeap);

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
int getLength(int index, HEAP minHeap){
    int length = minHeap.wordHeap[index].length;
    return length;
}

void swap(int index1, int index2, HEAP *minHeap){

    NODE temp = minHeap->wordHeap[index1];
    minHeap->wordHeap[index1] = minHeap->wordHeap[index2]; 
    minHeap->wordHeap[index2]= temp;


}





