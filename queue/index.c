#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue_node {
  int value;
  struct queue_node *next;
} queue_node;

typedef struct queue {
  int size;
  queue_node *front;
  queue_node *back;
} queue;

queue *create_queue() {
  queue *q = (queue *) malloc(sizeof(queue));
  q -> back = q -> front = NULL;
  q -> size = 0;
  return q;
}

bool empty_queue(queue *q) {
  return q -> size == 0;
}

void push_queue(queue *q, int value) {
  queue_node *qn = (queue_node *) malloc(sizeof(queue_node));
  qn -> next = NULL;
  qn -> value = value;

  if(empty_queue(q)) {
    q -> back = q -> front = qn;
  }
  else {
    q -> back -> next = qn;
    q -> back = qn;
  }
  q -> size++;
}

int pop_queue(queue *q) {
  if(empty_queue(q)) {
    printf("Error! The queue is empty.");
    return 0;
  }
  int value = q -> front -> value;
  queue_node *qn = q -> front;
  q -> front = q -> front -> next;
  free(qn);
  q -> size--;
  return value;
}

int main(int argc, char **argv) {

  queue *q = create_queue();
  push_queue(q, 5);
  push_queue(q, 1);
  push_queue(q, 574);
  push_queue(q, 9);
  push_queue(q, 6);

  while(!empty_queue(q)){
    printf("%d\n", pop_queue(q));
  }
  return 0;
}