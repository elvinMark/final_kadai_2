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
  lnode* info_last;
}tnode;

typedef struct onode{
  lnode* data;
  struct onode* next;
}onode;


tnode* createTnode(char* str);
void insertTerm(tnode** head,tnode *node);
void printTree(tnode* head);
void freeTree(tnode* head);
lnode* createLnode(int id);
void insertLnode(lnode** head,lnode** last,lnode* new);
void printList(lnode* head);
void freeList(lnode* head);
void insertTermAndList(tnode** head,char* str,int id);
tnode* search(tnode* head,char* query);
void push(onode** head,lnode* str);
void pop(onode** head);
lnode* andL(lnode* l1,lnode* l2);
lnode* orL(lnode* l1,lnode* l2);


int main(int argc, char* args[]){
  tnode* head;
  lnode *new_node,*l;
  tnode* aux;
  char buffer[BUFF_SIZE];
  char *token;
  int flag;
  int id;
  onode *list;
  FILE *p;

  head = NULL;
  list = NULL;

  if(argc<2){
    fprintf(stderr,"Please introduce the name of the file\n");
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
          insertLnode(&(aux->info),&(aux->info_last),new_node);
        }
      }
      token = strtok(NULL," ");
    }
  }

  fgets(buffer,BUFF_SIZE,stdin);
  buffer[strlen(buffer)-1] = '\0';
  
  token = strtok(buffer," ");
  while(token != NULL){
    if(strcmp(token,"AND")==0){
      /*l = list->data;
      pop(&list);
      l = andL(l,list->data);
      pop(&list);
      push(&list,l);*/
    }
    else if(strcmp(token,"OR")==0){ 
      l = list->data;
      pop(&list);
      l = orL(l,list->data);
      pop(&list);
      push(&list,l);
    }
    else{
      aux = search(head,token);
      push(&list,aux->info);
    }
    token = strtok(NULL," ");
  }
  printList(list->data);
  pop(&list);
  
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
  out->info_last = NULL;
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
void insertLnode(lnode** head,lnode** last,lnode* new){
  if(*head == NULL){
    *head = new;
    *last = new;
  }
  else{
    if((*last)->data != new->data){
      (*last)->next = new;
      (*last) = new;
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
void insertTermAndList(tnode** head,char* str,int id){
  tnode* new_n;
  lnode* new_l;
  new_n = createTnode(str);
  new_l = createLnode(id);
  new_n->info = new_l;
  new_n->info_last = new_l;
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

void push(onode** head,lnode* list){
  onode* new;
  new = (onode*)malloc(sizeof(onode));
  new->data = list;
  new->next = (*head);
  *head = new;
}
void pop(onode** head){
  onode* temp;
  temp = (*head)->next;
  free(*head);
  *head = temp;
}

lnode* andL(lnode* l1,lnode* l2){
  lnode* out;
  out = NULL;
  while(l1!=NULL){
    while(l2->data > l1->data){

    }
  }
}
lnode* orL(lnode* l1,lnode* l2){
  lnode* out,*last;
  out = NULL;
  last = NULL;
  
  while(l1!=NULL || l2!=NULL){
    while(l1->data > l2->data){
      insertLnode(&out,&last,createLnode(l2->data));
      l2 = l2->next;
      if(l2==NULL) break;
    }
    if(l2!=NULL){
      while(l1->data < l2->data){
        insertLnode(&out,&last,createLnode(l1->data));
        l1 = l1->next;
        if(l1==NULL) break;
      } 
    }
    else{
      while(l1!=NULL){
        insertLnode(&out,&last,createLnode(l1->data));
        l1 = l1->next;
      }
      break;
    }
  }
  return out;

  //if(l1!=NULL) return l1;
  //else if(l2!=NULL) return l2;
  //return NULL;
}