#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 21
#define COUNT 10

typedef struct tnode{
  char *data;
  struct tnode* right;
  struct tnode* left;
}tnode;

tnode* createTnode(char* str);
void insertTerm(tnode** head,tnode *node);
void printTree(tnode* head);
void freeTree(tnode* head);
void print2DT(tnode* head,int space);

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
  print2DT(head,0);
  freeTree(head);
  return 0;
}

tnode* createTnode(char* str){
  tnode* out;
  out = (tnode*) malloc(sizeof(tnode));
  out->data = (char*) malloc(sizeof(char)*STR_SIZE);
  strcpy(out->data,str);
  out->right = NULL;
  out->left = NULL;
  return out;
}

void insertTerm(tnode** head,tnode* node){
  char* tmp;
  if(*head == NULL){
    *head = node;
  }
  else{
    if(strcmp((*head)->data,node->data)<0){
      if((*head)->left != NULL || (*head)->right == NULL)
        insertTerm(&((*head)->right),node);
      else{
        tmp = (*head)->data;
        if(strcmp((*head)->right->data,node->data) < 0){
          (*head)->data = (*head)->right->data;
          (*head)->right->data = tmp;
          (*head)->left  = (*head)->right;
          (*head)->right = node;
        }
        else{
          (*head)->data = node->data;
          node->data = tmp;
          (*head)->left = node;
        }
      }
    }
    else{
      if((*head)->right != NULL || (*head)->left == NULL)
        insertTerm(&((*head)->left),node);
      else{
        tmp = (*head)->data;
        if(strcmp((*head)->left->data,node->data) < 0){
          (*head)->data = node->data;
          node->data = tmp;
          (*head)->right = node;
        }
        else{
          (*head)->data = (*head)->left->data;
          (*head)->left->data = tmp;
          (*head)->right = (*head)->left;
          (*head)->left = node;
        } 
      }
    }
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

void print2DT(tnode* head,int space){
  int i;
  if(head == NULL) return;
  space += COUNT;
  print2DT(head->left,space);
  for(i=COUNT;i<space;i++){
    printf(" ");
  }
  printf("%s\n",head->data);
  print2DT(head->right,space);
}