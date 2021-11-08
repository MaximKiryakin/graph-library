#include <stdio.h>
#include <stdlib.h>
    #include "graph_lib.h"

enum {BASE_MATRIX_SIZE = 1, MAX_LABEL = 1000};


//a function that determines the index by name
int get_index(struct Graph* a,int name1){
    int index = -1;
    for (int i = 0; i < a->current_size; i++){
        if (a->names[i] == name1){
            index = i;
            break;
        }
    }
    return index;
}

//graph initialization function
struct Graph* du_grapx(){
    struct Graph* a;
    a = (struct Graph*)malloc(sizeof(struct Graph));
    a->matrix = (int**)malloc(BASE_MATRIX_SIZE*sizeof(int*));
    for(int i = 0; i < BASE_MATRIX_SIZE; i++){
        a->matrix[i] = (int*)malloc(BASE_MATRIX_SIZE*sizeof(int));
    }
    for (int i = 0; i < BASE_MATRIX_SIZE; i++){
        for(int j = 0; j< BASE_MATRIX_SIZE; j++){
            a->matrix[i][j] = 0;
        }
    }
    a->current_size = BASE_MATRIX_SIZE;
    a->names = (int*)malloc(BASE_MATRIX_SIZE*sizeof(int));
    a->names[0] = -1;
    return a;
}

//graph delete function
void del_graph(struct Graph* an){
    int mas_size = an->current_size;
    for(int i = 0; i < mas_size; i++){
        free(an->matrix[i]);
    }
    free(an->matrix);
    free(an->names);
    free(an);
}

//function for adding a vertex to a graph
int add_vertex(struct Graph* a, int name){
    int size = a->current_size;
    if (a->names[0] != -1) {
        a->matrix = (int **) realloc(a->matrix, (size + 1) * sizeof(int *));
        a->matrix[size] = (int *) malloc((size + 1) * sizeof(int));
        for (int j = 0; j < size + 1; j++) {
            a->matrix[size][j] = 0;
        }
        for (int i = 0; i < size; i++) {
            a->matrix[i] = (int *)realloc(a->matrix[i], (size + 1) * sizeof(int));
            a->matrix[i][size] = 0;
        }
        a->current_size += 1;
        a->names = (int *) realloc(a->names, (size + 1) * sizeof(int));
        a->names[size] = name;
        return 1;
    }

    //this is the first vertex, we put it in the first cell (which is generated 
    //with the graph)
    a->names[0] = name;
    return 1;
}

//function of adding an edge to a graph
int add_edge(struct Graph* a,int name1, int name2, int weight, int both){
    int index1, index2;
    index1 = get_index(a, name1);
    index2 = get_index(a, name2);
    if (index1 == -1 || index2 == -1){
        printf("No vertex");
    } else {
        if (both == 0) {
            a->matrix[index1][index2] = weight;
        } else{
            a->matrix[index1][index2] = weight;
            a->matrix[index2][index1] = weight;
        }
    }
    return 1;
}

//function to remove an edge from a graph
int del_edge(struct Graph* a,int name1, int name2){
    int index1, index2;
    index1 = get_index(a, name1);
    index2 = get_index(a, name2);
    if (index1 == -1 || index2 == -1){
        printf("No vertex");
    } else {
        a->matrix[index1][index2] = 0;
    }
    return 1;
}

//function to remove a vertex from the graph
int del_node(struct Graph* a,int name1){
    //find the index of the name to be deleted
    int index1 = -1;
    int size = a->current_size;
    for (int i = 0; i < a->current_size; i++) {
        if (a->names[i] == name1) {
            index1 = i;
            break;
        }
    }
    if (index1 == -1){
        printf("No vertex");
        return 0;
    }
    // put the last line in place of the deleted line
    free(a->matrix[index1]);
    a->matrix[index1] = a->matrix[a->current_size - 1];
    //delete the last line

    //put the last column in place of the deleted column
    for(int i = 0; i < a->current_size -1 ; i++){
        a->matrix[i][index1] = a->matrix[i][a->current_size -1];
    }
    //delate the last row and column
    a->matrix = (int**)realloc(a->matrix, (size - 1)*sizeof(int*));
    for (int i = 0; i < size - 1; i++){
        a->matrix[i] = (int*)realloc(a->matrix[i], (size - 1)*sizeof(int));
    }
    //now the last vertex is the remote vertex
    a->names[index1] = a->names[size - 1];
    a->current_size -= 1;
    return 1;
}


//Dextra's algorithm
int* deikstra(struct Graph* a, int name1, int name2) {
    //create an array of labels for each vertex
    int labels[a->current_size];
    //create an array of flags visited / not visited
    int visit[a->current_size];
    //fill with an unreachable value
    for (int i = 0; i < a->current_size; i++) {
        labels[i] = MAX_LABEL;
        visit[i] = 0;
    }
    int index1, index2;
    index1 = get_index(a, name1);
    index2 = get_index(a, name2);
    if (index1 == -1 || index2 == -1){
        printf("No vertex");
        return NULL;
    }
    visit[index1] = 0;
    labels[index1] = 0;
    //create an array of ancestors for each vertex
    int* ver_mas = (int*)malloc((a->current_size)*sizeof(int));
    ver_mas[index1] = 0;


    for(int k = 0; k < a->current_size -1; k++) {
        int min_index = -1;
        int min_dist = MAX_LABEL;

        for (int i = 0; i < a->current_size; i++) {
            if (labels[i] < min_dist && visit[i] == 0) {
                //this is a neighbor who has not yet been visited
                min_dist = labels[i];
                min_index = i;
            }
        }

        for (int i = 0; i < a->current_size; i++) {
            int node = a->matrix[min_index][i];
            if (node > 0 && visit[i] == 0) {
                //this is a neighbor who has not yet been visited
                //check his label
                if (labels[min_index] + node < labels[i]) {
                    labels[i] = labels[min_index] + node;
                    //updated the label, remember the ancestor
                    ver_mas[i] = min_index;
                }
            }
        }
        visit[min_index] = 1;
    }

    int* ans_mas = (int*)malloc(sizeof(int));
    int temp_index = index2;
    int k = 0;
    ans_mas[0] = 1;
    while(temp_index != index1){
        k++;
        ans_mas = (int*) realloc(ans_mas, (k+1)*sizeof (int));
        ans_mas[0]++;
        ans_mas[k] = a->names[temp_index];
        temp_index = ver_mas[temp_index];

    }
    k++;
    ans_mas[0]++;
    ans_mas = (int*) realloc(ans_mas, (k+1)*sizeof (int));
    ans_mas[k] = a->names[temp_index];
    //inverting the array
    int ans_size = ans_mas[0];
    for(int i = 1; i < 1 + ans_size/2; i++){
        int temp =ans_mas[i];
        ans_mas[i] = ans_mas[ans_size - i];
        ans_mas[ans_size - i] = temp;
    }
    free(ver_mas);
    return ans_mas;
}


//Warshall's algorithm
struct Graph* warshall(struct Graph* initial){
    struct Graph* trans;
    trans = du_grapx();
    //duplicate graph
    int size = initial->current_size;

    for (int i = 0; i < size; i++){
        add_vertex(trans, i);
        trans->names[i] = initial->names[i];
    }


    for (int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            trans->matrix[i][j] = initial->matrix[i][j];
        }
    }
    trans->current_size = size;

    //do the transitive closure of the graph
    for (int k = 0; k < size; k++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                int a = trans->matrix[i][j] || (trans->matrix[i][k] && trans->matrix[k][j]);
                trans->matrix[i][j] = a;
            }
        }
    }
    return trans;
}



void print_matrix(struct Graph* gr2){
    for (int i = 0; i < gr2->current_size; i++) {
        for (int j = 0; j < gr2->current_size; j++) {
            printf("A[%d][%d] = %d ", gr2->names[i] , gr2->names[j], gr2->matrix[i][j]);
        }
        printf("\n");
    }
    printf("array of names\n");
    for (int i = 0; i < gr2->current_size; i++) {
        printf("%d ", gr2->names[i]);
    }
    printf("\n");
}



