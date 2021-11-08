
#include <stdlib.h>
#include "graph_lib.h"

int main() {

    //read the original graph
    struct Graph* gr1;
    gr1 = du_grapx();
    FILE* data;
    data = fopen("a.txt", "r");
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

    /*
    Let's use Warshall's algorithm and find the graph obtained from the original 
    one by closure. That is, if the original graph have path a-b-c, but there is no path
    a-c,the new graph will have it.
    */
    struct Graph* gr2;
    gr2 = warshall(gr1);
    int min_index = gr2->current_size + 1, max_index = -1;
    for (int i = 0; i < gr2->current_size; i++){
        if (gr2->matrix[i][i] == 1){
            //there is a cycle
            if (i < min_index){
                min_index = i;
            }
            if (i > max_index){
                max_index = i;
            }
        }
    }
    if (min_index == gr2->current_size + 1 || max_index == -1){
        printf("No two vertices lying in cycles");
        return 0;
    }
    printf("Minimum vertex number: %d\n", gr2->names[min_index]);
    printf("Maximum vertex number: %d\n", gr2->names[max_index]);
    //Воспользуемся алгоритмом Дейкстры, и найдем кратчайшее расстояние
    int* ans;
    ans = deikstra(gr1, gr2->names[min_index], gr2->names[max_index]);
    printf("Minimum path: ");
    for(int i = 1; i < ans[0]; i++){
        printf("%d ", ans[i]);
    }
    printf("\n");
    del_graph(gr2);
    del_graph(gr1);
    free(ans);
    return 0;
}