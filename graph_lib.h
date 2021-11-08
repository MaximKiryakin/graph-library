#include <stdio.h>


struct Graph{
    int** matrix;
    int current_size;
    int* names;         
};

int get_index(struct Graph* a,int name1);
struct Graph* du_grapx();
void del_graph(struct Graph* an);
int add_vertex(struct Graph* a, int name);
int add_edge(struct Graph* a,int name1, int name2, int weight, int both);
int del_edge(struct Graph* a,int name1, int name2);
int del_node(struct Graph* a,int name1);
int* deikstra(struct Graph* a, int name1, int name2);
void print_matrix(struct Graph* gr2);
struct Graph* warshall(struct Graph* initial);