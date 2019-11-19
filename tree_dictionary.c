#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct tree_t{
  //each node has a little that will form a word
  char letter;
  //flag that all the letters make a word, F = false, T = true. char is 1/2 bites of an int
  char is_word;
  //a single pointer to my parent node
  struct tree_t* parent;
  //pointer to a list of children
  struct tree_t* children;
  //points to the text node in the list
  struct tree_t* next;
}tree_t;

/*
WHATS LEFT TO BE DONE

add the flags to true at the end of a word

make the get word funciton



*/




/*
         d
       /   \
      a     o
    /  \   / \
   d   y  g   c
               \
                k
*/


//compare word can return a boolean, if it returns that a letter is not a child than we will not continue to triverse it's list


void add_children(tree_t**node, char word[],int max_index, int index);
void addNode(tree_t*parent_address, char new_letter, int is_word);
void print_tree(tree_t* list);
void print_list(tree_t* list);
void freeList(tree_t** head);
tree_t* create_node(char letter, tree_t *parent, int is_word);
void make_tree(char *filename, tree_t **root);
void decalre_root(tree_t **root);
void print_found_words(tree_t* list);
int main(int argc, char* argv[]){


  //used for making fake input
  char word[17];
  short word_size = 0;
  short word_index = 0;


  //declaring root
  tree_t *root = NULL;
  decalre_root(&root);
  /*
  printf("printing base tree\n");
  print_tree(root);
  printf("\n");
  */


  make_tree(argv[1], &root);

  /*
  printf("printing tree\n");
  print_tree(root);
  printf("\n");
  */

  /*
  printf("printing 'a' stuff\n");
  print_list(root->children); printf("\n");
  print_list(root->children->children); printf("\n");
  print_list(root->children->children->children); printf("\n"); //printf("- "); print_list(root->children->children->next->children);
  print_list(root->children->children->children->children); printf("\n");

  */

  print_found_words(root);







  /*

  word[0] = 'A'; //adding to A's tree
  word[1] = '@'; //adding the letter b
  word[2] = '\0';
  word_size = 2;

  add_children(&(root->children), word, word_size, 0 ); //if we aren't adding to the origional list we must add to root's sub tree

  word[0] = 'A';
  word[1] = '@';
  word[2] = '#';
  word[3] = '\0';
  word_size = 3;
  add_children(&(root->children), word, word_size, 0);

  */





  //print_tree(root);
  //printf("\n");
  /*
  print_tree(root->children);
  printf("\n");
  print_tree(root->children->children);
  printf("\n");
  print_tree(root->children->children->children);
  printf("\n");
  */




  freeList(&root);
  return 0;
}




//scans in our dictionary and adds all of the individual chars to our tree
void make_tree(char *file_name, tree_t **root){
  //opens the file
  FILE *fin = fopen(file_name, "r");

  //used for scanning and tokenizing
  char temp_input[20];
  int input_length;
  char *token;


  while(fgets(temp_input, 17, fin)){
    input_length = strlen(temp_input);

    //while the last char of temp_input is a non printable char
    while(temp_input[input_length] <= '!'){
      temp_input[input_length] = '\0';
      input_length--;
    }

    /*
    //makes the string lower case
    for(int i = 0; i < input_length; i++){
      temp_input[i] = tolower(temp_input[i]);
    }
    */

    add_children( &(*root)->children, temp_input, input_length, 0);
  }
}

//adds our first layer of children to root so the follwoing nodes have a base parent
void decalre_root(tree_t **root){

  *root = create_node(' ', NULL, 0);

  char word[4];
  word[0] = ' '; //it's a space so we add to root
  word[2] = '\0';
  int word_size = 2;

  //makes a base tree of the alphabet
  for(int i = 'a'; i <= 'z'; i++){
    word[1] = i;
    add_children(&(*root), word, word_size, 0);
  }
}

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
      free(new_child);
      return;
    }
    current_node = current_node->next;
  }

  //ensuring no duplicates
  if(current_node->letter == new_letter){
    free(new_child);
    return;
  }

  //adds our new node to our list
  current_node->next = new_child;
}


/* --------------------------- */
//recursive way of printing the tree, prints a node, than calls funciton again with the next node and children node
void print_tree(tree_t* list){

  //base case: if there is no list, do nothing
  if(list == NULL){
    return;
  }
  //visit
  printf("%c ", list->letter);

  //continues through the tree
  print_tree(list->next);
  print_tree(list->children);
}

void print_found_words(tree_t* list){
  //base case: if there is no list, do nothing
  if(list == NULL){
    return;
  }

  //if we find a flag, we print the letter from parent to parent
  if(list->is_word == 1){
    tree_t* temp = list;
    while(temp){
      printf("%c", temp->letter);
      temp = temp->parent;
    }
    printf("\n");
  }

  print_found_words(list->next);
  print_found_words(list->children);

}


void print_list(tree_t* list){

  //base case: if there is no list, do nothing
  if(list == NULL){
    return;
  }
  //visit
  printf("%c ", list->letter);

  //continues through the tree
  print_list(list->next);
}
/* --------------------------- */
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
