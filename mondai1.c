#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 21

//Define the structure of the tree nodes
typedef struct tnode{
  char data[STR_SIZE];
  struct tnode* right;
  struct tnode* left;
}tnode;

//function that create the tree nodes
tnode* createTnode(char* str);
//function that insert tree node in the binary tree
void insertTerm(tnode** head,tnode *node);
//function that print the binary tree
void printTree(tnode* head);
//function that free the heap used for the binary tree
void freeTree(tnode* head);

int main(int argc, char* args[]){
  //we define the main variables used in this program
  //head is the pointer to the root of the tree
  //temp is just a temporal pointer that we will use later
  tnode* head,*temp;
  //buffer will be used to read the strings from the file
  char buffer[STR_SIZE];
  //p is the file pointer
  FILE *p;
  //initialize head as empty (NULL)
  head = NULL;

  if(argc<2){
    fprintf(stderr,"Please introduce the name of the file");
    return -1;
  }
  //we read the file which filename was specified in the pipe
  p = fopen(args[1],"r");
  //we use a loop to read all the words from the file and 
  //insert them in binary tree
  while(fgets(buffer,STR_SIZE,p)){
    buffer[strlen(buffer)-1] = '\0';
    temp = createTnode(buffer);
    insertTerm(&head,temp);
  }
  //finally we print the tree
  printTree(head);
  //and free the mmeory used by tree
  freeTree(head);
  return 0;
}

//create a new tree node using malloc
//and initializing the pointer to right and left as NULL
tnode* createTnode(char* str){
  tnode* out;
  out = (tnode*) malloc(sizeof(tnode));
  strcpy(out->data,str);
  out->right = NULL;
  out->left = NULL;
  return out;
}

//insert the a node in the binary tree by recursion
void insertTerm(tnode** head,tnode* node){
  if(*head == NULL){
    *head = node;
  }
  else{
    if(strcmp((*head)->data,node->data)<0)
      insertTerm(&((*head)->right),node);
    else
      insertTerm(&((*head)->left),node);
  }
}

//print the binary tree by recursion
//print the left tree, 
//then the data in current node and finaly 
//print the right tree
void printTree(tnode* head){
  if(head==NULL)
    return;
  printTree(head->left);
  printf("%s\n",head->data);
  printTree(head->right);
 
}

//free the memory occupied by the tree by recursion
void freeTree(tnode *head){
  tnode* r;
  tnode* l;
  if(head==NULL)
    return;
  r = head->right;
  l = head->left;
  free(head);
  freeTree(r);
  freeTree(l);
}
