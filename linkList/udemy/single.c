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

void push_front_list(list *l, int value) {
  list_node *ln = (list_node *) malloc(sizeof(list_node));
  ln -> value = value;
  ln -> next = l -> head;
  l -> head = ln;
  l -> size++;
}

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

int main(int argc, char **argv) {
  list *l = create_list();
  push_front_list(l, 3);
  push_front_list(l, 62);
  push_front_list(l, 74);
  push_front_list(l, 8);
  push_front_list(l, 1102);
  while(!empty_list(l)){
    printf("%d\n", pop_front_list(l));
  }

  return 0;
}
