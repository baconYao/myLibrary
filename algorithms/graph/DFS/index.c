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
  graph *g = create_graph(13, false);       //建立一個有13個點的無向圖
  
  graph_add_edge(g,0,1,1);
  graph_add_edge(g,1,2,12);
  graph_add_edge(g,1,3,10);
  graph_add_edge(g,2,4,11);
  graph_add_edge(g,2,5,13);
  graph_add_edge(g,3,5,12);
  graph_add_edge(g,3,7,13);
  graph_add_edge(g,4,6,9);
  graph_add_edge(g,5,6,7);
  graph_add_edge(g,6,7,15);
  graph_add_edge(g,8,9,12);
  graph_add_edge(g,8,10,10);
  graph_add_edge(g,9,10,10);
  graph_add_edge(g,10,11,9);
  graph_add_edge(g,11,12,10);

  return 0;
}
