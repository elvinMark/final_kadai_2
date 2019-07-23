#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 22
#define BUFF_SIZE 1025

typedef struct lnode{
  int data;
  int id;
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
lnode* createLnode(int id,int id1);
void insertLnode(lnode** head,lnode* new);
void printList(lnode* head);
void freeList(lnode* head);
void insertTermAndList(tnode** head,char* str,int id,int id1);
tnode* search(tnode* head,char* query);

int main(int argc, char* args[]){
  tnode* head;
  lnode *new_node;
  tnode* aux;
  char buffer[BUFF_SIZE];
  char *token;
  int flag;
  int id;
  int id1;
  FILE *p;

  head = NULL;

  if(argc<2){
    fprintf(stderr,"Please introduce the name of the file\n");
    return -1;
  }

  p = fopen(args[1],"r");
  while(fgets(buffer,BUFF_SIZE,p)){
    buffer[strlen(buffer)-1] = '\0';
    token = strtok(buffer,"\t ");
    flag = 0;
    id = 0;
    id1 = 0;
    while(token!=NULL){
      if(flag==0){
        id = atoi(token);
        flag++;
      }
      else if(flag == 1){
        id1 = atoi(token);
        flag++;
      }
      else{
        aux = search(head,token);
        if(aux==NULL)
          insertTermAndList(&head,token,id,id1);
        else{
          new_node = createLnode(id,id1);
          insertLnode(&(aux->info),new_node);
        }
      }
      token = strtok(NULL,"\t ");
    }
  }

  scanf("%s",buffer);
  if((aux = search(head,buffer))==NULL)
    printf("Not found\n");
  else 
    printList(aux->info);
  
  freeTree(head);
  
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

lnode* createLnode(int id,int id1){
  lnode* new;
  new = (lnode *)malloc(sizeof(lnode));
  new->data=id;
  new->id = id1;
  new->next = NULL;
  return new;
}
void insertLnode(lnode** head,lnode* new){
  lnode *temp,*temp1;
  if(*head == NULL){
    *head = new;
  }
  else{
    temp=(*head);
    temp1 = temp->next;
    if(temp->id < new->id){
      new->next = *head;
      (*head) = new;
    }
    else{
      while(temp1 != NULL){
        if(temp1->id < new->id) break;
        temp1 = temp1->next;
        temp = temp->next;
      }
      if(temp->data == new->data) return;
      new->next = temp1;
      temp->next = new;
    }
  }
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
void insertTermAndList(tnode** head,char* str,int id,int id1){
  tnode* new_n;
  lnode* new_l;
  new_n = createTnode(str);
  new_l = createLnode(id,id1);
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
tnode* search(tnode* head,char* query){
  tnode* out = NULL;
  if(head == NULL)
    return NULL;
  if(strcmp(head->data,query)==0)
    return head;
  else{
    if((out = search(head->left,query))!=NULL)
      return out;
    if((out = search(head->right,query))!=NULL)
      return out;
  }
  return NULL;
}
