#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree_node {
  int value;
  struct tree_node *left_child;
  struct tree_node *right_child;
} tree_node;

typedef struct tree {
  int size;
  tree_node *root;
} tree;

tree *create_tree() {
  tree *t = (tree *) malloc(sizeof(tree));
  t -> root = NULL;
  t -> size = 0;
  return t;
}

bool empty_tree(tree *t) {
  return t -> size == 0;
}



int main(int argc, char **argv) {


  return 0;
}
