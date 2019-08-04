#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 22
#define BUFF_SIZE 1005

//Define the structure of the linked list nodes
typedef struct lnode{
  int data;
  struct lnode* next;
}lnode;

//Define the structure of the tree nodes
typedef struct tnode{
  char data[STR_SIZE];
  struct tnode* right;
  struct tnode* left;
  lnode* info;
  lnode* info_last;
}tnode;


//function that creates a new tree node
tnode* createTnode(char* str);
//function that inserts a tree node in the binary tree
void insertTerm(tnode** head,tnode *node);
//function that prints the binary tree
void printTree(tnode* head);
//function that frees the memory used by the binary tree
void freeTree(tnode* head);
//function that creates a new list node
lnode* createLnode(int id);
//function that inserts the node into the linked list (at the end)
void insertLnode(lnode** head,lnode** last,lnode* new);
//function that prints the linked list
void printList(lnode* head);
//function that frees the memory occupied by the linked list
void freeList(lnode* head);
//function that creates a new tree node and insert a new list node to 
//its linked list and finally insert that tree node in the binary tree
void insertTermAndList(tnode** head,char* str,int id);
//function that search an specific data in the binary tree
tnode* search(tnode* head,char* query);

int main(int argc, char* args[]){
  //head is the pointer to the root of the binary tree
  tnode* head;
  //This node will be used when we want to a new linked list node into 
  //certain linked list
  lnode *new_node;
  //temporal pointer that will be used later
  tnode* aux;
  //buffer will be used to read strings later on
  char buffer[BUFF_SIZE];
  //char pointer that will used for the string tokenizer
  char *token;
  //flag will control whether we are reading an id or words.
  int flag;
  int id;
  //file pointer
  FILE *p;

  //initialize the binary tree as empty (NULL)
  head = NULL;

  if(argc<2){
    fprintf(stderr,"Please introduce the name of the file\n");
    return -1;
  }

  //read the file wichi filename is specified in the pipe
  p = fopen(args[1],"r");
  //read each line of the file and tokenize it. the first token will correspond to the id
  // and the rest of the tokens will be words that are going to be inserted in the tree
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
        //we first check wheteher this word is already in the tree or not
        aux = search(head,token);
        //if that word was not already in the tree then insert it along with the id
        if(aux==NULL)
          insertTermAndList(&head,token,id);
        else{
          //if that word was already in the tree, then just insert the new id into its linked list
          new_node = createLnode(id);
          insertLnode(&(aux->info),&(aux->info_last),new_node);
        }
      }
      token = strtok(NULL," ");
    }
  }

  //read the query from the user and print the result
  scanf("%s",buffer);
  if((aux = search(head,buffer))==NULL)
    printf("Not found\n");
  else 
    printList(aux->info);
  
  freeTree(head);
  
  return 0;
}

//create a new tree node and initialize the pointer to the right and left as NULL. 
//Also the pointers used for the linked list initialize as NULL since the list is empty
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

//insert a new tree node in the binary tree by recursion
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

//print the binary tree also by recursion
void printTree(tnode* head){
  if(head==NULL)
    return;
  printTree(head->left);
  printf("%s\n",head->data);
  printTree(head->right); 
}

//free the binary tree by recursion
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

//create a new list node with the specified input and initialize 
//the next element pointer as NULL
lnode* createLnode(int id){
  lnode* new;
  new = (lnode *)malloc(sizeof(lnode));
  new->data=id;
  new->next = NULL;
  return new;
}

//insert a new node in the list at the end using the 
//pointer last which is always pointing at the last element of the list
//of course if the list is empty we initialize head and last as the new element
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

//print the list by recursion
void printList(lnode* head){
  while(head!=NULL){
    printf("%d\n",head->data);
    head = head->next;
  }
}

//free the memory used by the list by recursion
void freeList(lnode* head){
  lnode* temp;
  while(head!=NULL){
    temp = head->next;
    free(head);
    head = temp;
  }
}

//create a new tree node and also insert the id into its linked list.
//and insert this node into the binary tree
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

//search in the binary tree by recursion
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
