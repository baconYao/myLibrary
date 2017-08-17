/*
  future work:
    1. 實作delete_node function
    2. 實作find_node function
*/

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

void insert(tree *t, int value) {
  // 初始化一個tree node
  tree_node *tn = (tree_node *) malloc(sizeof(tree_node));
  tn -> value = value;
  tn -> left_child =  tn -> right_child = NULL;
  
  // 檢查數是否為空
  if(empty_tree(t)) {
    // 將此data設為root
    t -> root = tn;
    t -> size++;
    printf("Add data 『%d』 to tree.\n", value);      
    return;
  }

  tree_node *tmpNode = t -> root;
  // 插入新node
  while(true) {
    // 檢查左子樹
    if(value < tmpNode -> value) {
      // 沒有左節點
      if(tmpNode -> left_child == NULL) {
        tmpNode -> left_child = tn;
        t -> size++;
        printf("Add data 『%d』 to tree.\n", value);      
        break;
      }
      else {
        // 移動到下個左node
        tmpNode = tmpNode -> left_child;
      }
    }
    // 檢查右子樹
    else if(value > tmpNode -> value) {
      // 沒有右節點
      if(tmpNode -> right_child == NULL) {
        tmpNode -> right_child = tn;
        t -> size++;
        printf("Add data 『%d』 to tree.\n", value);        
        break;
      } 
      else {
        // 移動到下個右node
        tmpNode = tmpNode -> right_child;
      }
    }
    else {
      // 找到value一樣的節點，代表已有資料在裡面
      printf("The data 『%d』 already exists in tree.\n", value);
      return;
    }
  }
}

void print_tree(tree_node *root) {
  if(root == NULL) {
    return;
  }
  // 遞迴方式印出內容，由小到大印出(改變printf位置可改變印出順序)
  print_tree(root -> left_child);
  printf("%d\n", root -> value);
  print_tree(root -> right_child);
}

int main(int argc, char **argv) {
  tree *t = create_tree();
  insert(t, 5);
  insert(t, 9);
  insert(t, 2);
  insert(t, 7);
  insert(t, 0);
  insert(t, 5);
  insert(t, 8);
  insert(t, 1);
  insert(t, 3);

  print_tree(t -> root);
  return 0;
}
