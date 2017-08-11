#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct stack_node {
  int value;
  struct stack_node *next;
} stack_node;

typedef struct stack {
  stack_node *top;
  int size;
} stack;

stack *create_stack() {
  stack *s = (stack *) malloc(sizeof(stack));
  s->size = 0;
  s->top = NULL;
  return s;
}

bool empty_stack(stack *s) {
  return s->size == 0;
}

void push(stack *s, int value) {
  stack_node *n  = (stack_node *) malloc(sizeof(stack_node));
  n->value = value;
  n->next = s->top;
  s->top = n;
  s->size++;
}

int pop(stack *s) {
  int value = s->top->value;
  stack_node *sn = s->top;        //用來暫時承接要被取出的第一個element
  s->top = s->top->next;
  s->size--;
  free(sn);                       //第一個element被取出後，記憶體位置必須被釋放
  return value;
}

int main(int argc, char **argv) {
  stack *s = create_stack();
  push(s, 5);
  push(s, 9);
  push(s, 3);
  while(!empty_stack(s)){
    printf("%d\n", pop(s));
  }

  return 0;
};