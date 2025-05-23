#define _strdup strdup

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i, j, k;
  for(i = 0; i < 9; i++) {
    int seen[10] = {0};
    for(j = 0; j < 9; j++) {
      int val = n->sudo[i][j];
      if(val != 0){
        if(seen[val]) return 0;
        seen[val] = 1;
      }
    }
  }

  for (j = 0; j < 9; j++) {
      int seen[10] = {0};
      for (i = 0; i < 9; i++) {
          int val = n->sudo[i][j];
          if (val != 0) {
              if (seen[val]) return 0;
              seen[val] = 1;
          }
      }
  }

  for (k = 0; k < 9; k++) {
      int seen[10] = {0};
      for (int p = 0; p < 9; p++) {
          int i = 3 * (k / 3) + (p / 3);
          int j = 3 * (k % 3) + (p % 3);
          int val = n->sudo[i][j];
          if (val != 0) {
              if (seen[val]) return 0;
              seen[val] = 1;
          }
      }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, j;
    for(i = 0; i < 9; i++){
      for(j = 0; j < 9; j++){
        if(n->sudo[i][j] == 0){
          for(int val =  1; val <= 9; val++){
            Node* adj = copy(n);
            adj->sudo[i][j] = val;
            if(is_valid(adj)){
              pushBack(list, adj);
            } else {
              free(adj);
            }
          }
          return list;
        }
      }
    }
    return list;
}

int is_final(Node* n){
  int i, j;
  for(i = 0; i < 9; i++){
    for(j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0){
        return 0;
      }
    }
  }  
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S = createStack();
  push(S, initial);
  while(!is_empty(S)){
    Node* current = top(S);
    pop(S);
    (*cont)++;
    if(is_final(current)){
      return current;
    }
    List* adj = get_adj_nodes(current);
    Node* adjNode = first(adj);
    while(adjNode != NULL){
      push(S, adjNode);
      adjNode = next(adj);
    }
    free(current);
    clean(adj);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/