#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_lib.h"



int main() {

    /*
    Checking library functions
    */

    //read the graph for tests
    struct Graph* gr1;
    gr1 = du_grapx();
    FILE* data;
    data = fopen("test_graph.txt", "r");
    if (!data){
        printf("can not open the file");
        return 1;
    }
    int nodes_number;
    char buffer[80];
    fgets(buffer, 80, data);
    sscanf(buffer,"%i",&nodes_number);

    for (int i = 0; i < nodes_number; i++){
        add_vertex(gr1, i+1);   // HERE i+1 - numbering of vertices in the file
        // from 1, i + 0 - from 0
    }

    int n1, n2, weight, direction;
    while(fgets(buffer, 82, data)){
        sscanf(buffer,"%i %i %i %i",&n1,&n2,&weight, &direction);
        add_edge(gr1, n1, n2, weight, direction);
    }
    fclose(data);


    //print the adjacency matrix of the original graph:
    printf("The adjacency matrix of the original graph\n");
    print_matrix(gr1);

    //vertex removal function check
    printf("Adjacency matrix of the graph after removing vertices 3 and 5\n");
    del_node(gr1, 3);
    del_node(gr1, 5);

    print_matrix(gr1);

    //vertex addition functions check
    add_vertex(gr1, 3);
    add_vertex(gr1, 5);

    printf("Adjacency matrix of the graph after adding vertices 3 and 5\n");
    print_matrix(gr1);

    //checking the add edge function
    add_edge(gr1, 4, 3, 3, 0);
    add_edge(gr1, 3, 5, 1, 0);
    add_edge(gr1, 5, 2, 1, 0);

    printf("Adjacency matrix of a graph after adding edges 4-(3)-3; 3-(1)-5; 5-(1)-2;\n");
    print_matrix(gr1);

    //checking the edge removal function
    del_edge(gr1, 5, 2);
    del_edge(gr1, 1, 2);

    printf("Adjacency matrix of a graph after removing edges 5-2; 1-2\n");
    print_matrix(gr1);

    //checking Dejkstra's algorithm
    //brought back the removed edge
    add_edge(gr1, 1, 2, 3, 0);

    int* ans;
    ans = deikstra(gr1, 1, 5);
    printf("Dejkstra minimum path:\n");
    for(int i = 1; i < ans[0]; i++){
        printf("%d ", ans[i]);
    }
    free(ans);
    printf("\n");

    //check of Warshall's algorithm
    struct Graph* gr2;
    gr2 = warshall(gr1);
    printf("Printing a closed graph treated with Warshall's algorithm\n");
    print_matrix(gr2);

    del_graph(gr2);
    del_graph(gr1);
    return 0;
}
