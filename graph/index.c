#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct edge_node {
  int v;    //the number of the node which we connectted to，這個點連到的下一個點
  int weight;   //兩點間edge的weight
  struct edge_node *next;
} edge_node; 

typedef struct graph {
  edge_node **edges;    //equal * edge[]，建立一個array，沒有大小限制
  int nb_nodes;         //點的數量
  int nb_edges;         //邊的數量
  bool isDirected;      //是否有向
} graph; 

graph *create_graph(int nb_nodes, bool isDirected) {
  /*
    初始化
  */ 
  graph *g = (graph *) malloc(sizeof(graph));
  g -> nb_nodes = nb_nodes;
  g -> nb_edges = 0;
  g -> isDirected = isDirected;
  //根據nb_nodes的數量來配置記憶體空間給edges array  
  g -> edges = (graph **) malloc(sizeof(graph *) * nb_nodes);
  int u;  //點u
  for(u = 0; u < g -> nb_nodes; u++) {
    g -> edges[u] = NULL;   //初始化每個點u
  }
  return g;
}

void print_graph(graph *g) {
  int u;
  // for every list
  for(u = 0; u < g -> nb_nodes; u++) {
    printf("%d --> ", u);
    // 印出此list上所有的node(表示有連起來的點)
    edge_node *e = g -> edges[u];
    while(e != NULL) {
      printf("%d ", e -> v);
      e = e -> next;
    }
    printf("\n");
  }
}

// 將點u和新增的點v相連且給這條edge一個weight
void graph_add_edge(graph *g, int u, int v, int weight) {
  edge_node *e = (edge_node *) malloc(sizeof(edge_node));
  e -> v = v;
  e -> weight = weight;
  e -> next = g -> edges[u];
  g -> edges[u] = e;
  // 若是無向圖
  if(!g -> isDirected) {
    e = (edge_node *) malloc(sizeof(edge_node));
    e -> v = u;
    e -> weight = weight;
    e -> next = g -> edges[v];
    g -> edges[v] = e;
  }
  g -> nb_edges++;
}

int main(int argc, char **argv) {
  graph *g = create_graph(6, true);       //建立一個有六個點的有向圖
  /* 插入新點和配置edge的weight */
  // 將點2和4相連，且wight為1
  graph_add_edge(g, 2,4,1);
  // 將點2和5相連，且wight為1
  graph_add_edge(g, 2,5,1);
  print_graph(g);

  printf("\n");

  graph *g2 = create_graph(6, false);       //建立一個有六個點的無向圖
  /* 插入新點和配置edge的weight */
  // 將點2和4相連，且wight為1
  graph_add_edge(g2, 2,4,1);
  // 將點2和5相連，且wight為1
  graph_add_edge(g2, 2,5,1);
  print_graph(g2);

  return 0;
}





/*
  Output:

  directed
  0 -->
  1 -->
  2 --> 5 4
  3 -->
  4 -->
  5 -->

  indirected
  0 -->
  1 -->
  2 --> 5 4
  3 -->
  4 --> 2
  5 --> 2

*/ 