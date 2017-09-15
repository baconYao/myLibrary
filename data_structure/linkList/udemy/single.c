#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list_node {
  int value;
  struct list_node *next;
} list_node;

typedef struct list {
  int size;
  list_node *head;
} list;

list *create_list() {
  list *l = (list *) malloc(sizeof(list));
  l -> head = NULL;
  l -> size = 0;
  return l;
}

bool empty_list(list *l) {
  return l -> size == 0;
}
// 從前面放入
void push_front_list(list *l, int value) {
  list_node *ln = (list_node *) malloc(sizeof(list_node));
  ln -> value = value;
  ln -> next = l -> head;
  l -> head = ln;
  l -> size++;
}

// 從後面放入
void push_back_list(list *l, int value) {
  list_node *ln = (list_node *) malloc(sizeof(list_node));
  ln -> value = value;
  ln -> next = NULL;
  list_node *p = l -> head;
  while(p != NULL && p -> next != NULL){
    p = p -> next;        //指向下一個node的memory address
  }
  if( p == NULL) {        //list is empty
    l -> head = ln;
  } else {
    p -> next = ln;       //指向新的node
  }

  l -> size++;
}

// 從前面拿出
int pop_front_list(list *l) {
  if(empty_list(l)) {
    printf("Error, empty list!\n");
    return 0;
  }
  int value = l -> head -> value;
  list_node *ln = l -> head;
  l -> head = l -> head -> next;
  free(ln);
  l -> size--;
  return value;
}

// 從後面拿出
int pop_back_list(list *l) {
  if(empty_list(l)) {
    printf("Error, empty list!\n");
    return 0;
  }
  if(l -> head -> next == NULL) {       //
    int value = l -> head -> value;
    free(l -> head);
    l -> head = NULL;
    l -> size--;
    return value;
  }

  list_node *ln = l -> head;
  while(ln -> next -> next != NULL) {
    ln = ln -> next;
  }
  int value = ln -> next -> value;
  free(ln -> next);
  ln -> next = 0;       //指向NULL
  l -> size--;
  return value;
}

void reverseList(list *l) {
  list_node *prev = NULL;
  list_node *curr = l -> head;
  while(curr != NULL) {
    list_node *nextTmp = curr -> next;
    curr -> next = prev;
    prev = curr;
    curr = nextTmp;
  }

  l -> head = prev;
}


int main(int argc, char **argv) {
  list *l = create_list();
  push_back_list(l, 3);
  push_back_list(l, 62);
  push_back_list(l, 74);
  push_back_list(l, 8);
  push_back_list(l, 1102);
  while(!empty_list(l)){
    printf("%d\n", pop_front_list(l));
  }

  printf("Reverse-----------------------------------------\n");

  push_back_list(l, 3);
  push_back_list(l, 62);
  push_back_list(l, 74);
  push_back_list(l, 8);
  push_back_list(l, 1102);
  reverseList(l);
  while(!empty_list(l)){
    printf("%d\n", pop_front_list(l));
  }

  return 0;
}
