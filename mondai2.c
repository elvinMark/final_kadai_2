#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 22
#define BUFF_SIZE 1005

typedef struct lnode{
  int data;
  struct lnode* next;
}lnode;

typedef struct tnode{
  char data[STR_SIZE];
  struct tnode* right;
  struct tnode* left;
  lnode* info;
}tnode;


tnode* createTnode(char* str);
void insertTerm(tnode** head,tnode *node);
void printTree(tnode* head);
void freeTree(tnode* head);
lnode* createLnode(int id);
void insertLnode(lnode* head,lnode* new);
void printList(lnode* head);
void freeList(lnode* head);
void insertTermAndList(tnode** head,char* str,int id);
lnode* search(tnode* head,char* query);

int main(int argc, char* args[]){
  tnode* head;
  lnode* aux,*new_node;
  char buffer[BUFF_SIZE];
  char *token;
  int flag;
  int id;
  FILE *p;

  head = NULL;

  if(argc<2){
    fprintf(stderr,"Please introduce the name of the file");
    return -1;
  }

  p = fopen(args[1],"r");
  while(fgets(buffer,BUFF_SIZE,p)){
    buffer[strlen(buffer)-1] = '\0';
    token = strtok(buffer,"\t");
    flag = 1;
    id = 0;
    while(token!=NULL){
      if(flag){
	id = atoi(token);
	flag = 0;
      }
      else{
	aux = search(head,token);
	if(aux==NULL)
	  insertTermAndList(&head,token,id);
	else{
	  new_node = createLnode(id);
	  insertLnode(aux,new_node);
	}
      }
      token = strtok(NULL," ");
      }
  }

  scanf("%s",buffer);
  if((aux = search(head,buffer))==NULL)
    printf("Not found\n");
  else 
    printList(aux);
  
  return 0;
}

tnode* createTnode(char* str){
  tnode* out;
  out = (tnode*) malloc(sizeof(tnode));
  strcpy(out->data,str);
  out->right = NULL;
  out->left = NULL;
  out->info = NULL;
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
  freeList(head->info);
  free(head);
  freeTree(r);
  freeTree(l);
}

lnode* createLnode(int id){
  lnode* new;
  new = (lnode *)malloc(sizeof(lnode));
  new->data=id;
  new->next = NULL;
  return new;
}
void insertLnode(lnode* head,lnode* new){
  while(head->next !=NULL) head = head->next;
  if(head->data != new->data)
    head->next = new;
}
void printList(lnode* head){
  while(head!=NULL){
    printf("%d\n",head->data);
    head = head->next;
  }
}
void freeList(lnode* head){
  lnode* temp;
  while(head!=NULL){
    temp = head->next;
    free(head);
    head = temp;
  }
}
void insertTermAndList(tnode** head,char* str,int id){
  tnode* new_n;
  lnode* new_l;
  new_n = createTnode(str);
  new_l = createLnode(id);
  new_n->info = new_l;
  if(*head == NULL){
    *head = new_n;
  }
  else{
    if(strcmp((*head)->data,new_n->data)<0)
      insertTerm(&((*head)->right),new_n);
    else
      insertTerm(&((*head)->left),new_n);
  }
}
lnode* search(tnode* head,char* query){
  lnode* out = NULL;
  if(head == NULL)
    return NULL;
  if(strcmp(head->data,query)==0)
    return head->info;
  else{
    if((out = search(head->left,query))!=NULL)
      return out;
    if((out = search(head->right,query))!=NULL)
      return out;
  }
  return NULL;
}
