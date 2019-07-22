#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 21

typedef struct tnode{
  char data[STR_SIZE];
  struct tnode* right;
  struct tnode* left;
}tnode;

tnode* createTnode(char* str);
void insertTerm(tnode** head,tnode *node);
void printTree(tnode* head);
void freeTree(tnode* head);

int main(int argc, char* args[]){
  tnode* head,*temp;
  char buffer[STR_SIZE];
  FILE *p;
  head = NULL;
  if(argc<2){
    fprintf(stderr,"Please introduce the name of the file");
    return -1;
  }
  p = fopen(args[1],"r");
  while(fgets(buffer,STR_SIZE,p)){
    buffer[strlen(buffer)-1] = '\0';
    temp = createTnode(buffer);
    insertTerm(&head,temp);
  }
  printTree(head);
  freeTree(head);
  return 0;
}

tnode* createTnode(char* str){
  tnode* out;
  out = (tnode*) malloc(sizeof(tnode));
  strcpy(out->data,str);
  out->right = NULL;
  out->left = NULL;
  return out;
}

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

void printTree(tnode* head){
  if(head==NULL)
    return;
  printTree(head->left);
  printf("%s\n",head->data);
  printTree(head->right);
 
}

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
