The graph_lib library
Main functions:

1) du_grapx () - creating a graph.
struct Graph * du_grapx ();
The function returns a pointer to a structure-graph
Structure fields:
    names - vertex names field (how the user named the vertex)
    matrix - the adjacency matrix of the graph. In its cells, if there is an edge, there is
its weight. The row number is the index of the first vertex, the column is the second.
    current_size - the current dimension of the matrix.

2) deleteGraph - function for deleting a graph.
void del_graph (struct Graph * an);
Accepts a pointer to a graph structure and destroys it, freeing it's memory.

3) add_vertex - function for adding a vertex.
int add_vertex (struct Graph * a, int name);
    a - structure - graph; 
    name - the name of the vertex.

4) add_edge - function for adding an edge.
int add_edge (struct Graph * a, int name1, int name2, int weight, int both);
    a - graph
    name1 - name of the first vertex
    name2 - the name of the second vertex. 
    weight - weight (positive number).
    both - a parameter that takes two values:
        1 - create an edge in two directions
        0 - create an edge name1 -> name2.
If no vertices are added, a warning is displayed.

5) del_edge - edge removal function.
int del_edge (struct Graph * a, int name1, int name2);
    a - structure-graph
    name1, name2 - vertices between which you need to remove the edge.
    If no edge is added, a warning is displayed.

6) del_node - removal of a vertex.
int del_node (struct Graph * a, int name1);
The function takes a structure - a graph and a vertex name. Deletes a vertex
from the graph. If there is no top - warning.


7) deikstra Dijkstra's algorithm.
int * deikstra (struct Graph * a, int name1, int name2);
    a - structure-graph
    name1, name2 - names of vertices between which
the shortest path is sought (meaning by weight). The return value is 
an array of int elements, the first element of which is the length of the array. 
The way is supposed to be found.

8) print_matrix - function for printing an adjacency matrix.
void print_matrix (struct Graph * gr2);
    gr2 - structure-graph.
Output: printing adjacency matrix to console, printing variable names.

9) warshall - Warshall's algorithm.
struct Graph * warshall (struct Graph * initial);
    initial - structure-graph. 
The return value is a structure-graph.

The essence of the algorithm: the transitive closure of the relation on the set
peaks. That is, in simpler terms, the adjacency matrix of the returned graph
shows if there is a path from vertex a to vertex b.

The task that was solved using the library:
Formulation of the problem:
It is necessary to find all the vertices of the graph that lie in the cycle.
That is, when we leave the vertex, there is an opportunity to return to it.
Of all these vertices, you need to choose two: with the maximum and minimum number and
find the shortest distance between them. The weights of the edges of the graph are strictly positive.
The graph is directed. Two such vertices are  existing.

How the graph is read.
The parameters are set in the text file.
1 number - the number of vertices.
further four numbers: name1 name2 weight direction.
Important: the numbering of vertices in the file starts from one.
Accordingly, names must be passed to Dijkstra's function, starting with 1.
When read, they are automatically generated 1 ... n.

Assembly:
make - assembly of the program that solves the problem. Result file solution
make test - building a program that demonstrates how the library functions work
make clen - clears all binaries


