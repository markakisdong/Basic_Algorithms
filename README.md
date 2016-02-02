# basic algorithms
Some basic algorithms implemented in C

bellman_ford:

        computes shortest paths from a single source vertex to all of the other vertices in a weighted directed graph.
        usage: ./a.out <input file> <source>
        input file:
            line1: number of vertices.
            line2~n: adjacency matrix of the graph.
        source:
            may the source be with you.
        output: bellman_ford_out.txt

find_max_sum_in_array:

        find maximum sub array in an array, only need to assign the number of elements. The array is generated randomly.
        usage: ./a.out
        elements: the size of the random array
        output: stdout and running times.
        
    
find_max_sum_in_array_optimized:

        the optimized version of finding the maximum sub array in an array.
        
    
johnson:

        computes shortest paths between all pairs of vertices in a sparse, edge weighted, directed graph.
        The algorithm works as this:
        1. add a node q to the graph, connected by zero-weight edges to each of the other nodes.
        2. do bellman ford algorithm from source q, resulting h(v) of a path from q to v.
           Terminated if negative weight cycle is found.
        3. reweight the graph by w(u, v)' = w(u, v) + h(u) - h(v)
        4. remove q and do dijkstra algorithm to find the shortest paths from each node s to 
           every other vertex in the reweighted graph.
        usage: ./a.out <input file>
        input file:
            line1: number of vertices
            line2: number of edges
            line3~n: <vertex> <vertex> <edge weight>
        output: johnson_out.txt

    
merge-inversion:

        counts how many inversions used in a merge sort.
        usage: ./a.out
        10 numbers: give an array.
        output: stdout inversions.


nqueen:

        the well-known n queen problem.
        usage: ./a.out <number of queens>
        output: stdout solutions.


optimal_bst:

        computes the optimal binary search tree given probabilities pi and qj.
        usage: ./a.out <input file>
        input file:
            line1: (node 1, probability p1) (node 2, proba...)
            line2: (dummy keys 0, probability q0) (dummy keys 1, proba...)
        output: optimal_bst_out.txt


to be continued...
