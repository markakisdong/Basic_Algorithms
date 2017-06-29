# Algorithms
Some algorithms implemented in C.

## Bellman-Ford:
Computes shortest paths from a single source to all other vertices in a weighted directed graph.

```bash
./a.out <input file> <source>
```
`input file`: line1: number of vertices, line2~n: adjacency matrix of the graph.<br>
`source`: the source vertice.

This will save a `bellman_ford_out.txt` file to the directory.

## Find Max Sum in Array:
Find maximum sub-array in an array.

```bash
./a.out
```
`elements`: the size of the randomly generated array

Also provide an optimized version.

## Johnson Algorithm:
Computes shortest paths between all pairs of vertices in a sparse, edge weighted, directed graph.

The algorithm works as this:
1. add a node q to the graph, connected by zero-weight edges to each of the other nodes.
2. do bellman ford algorithm from source q, resulting h(v) of a path from q to v. Terminate if negative weight cycle is found.
3. reweight the graph by w(u, v)' = w(u, v) + h(u) - h(v)
4. remove q and do dijkstra algorithm to find the shortest paths from each node s to every other vertex in the reweighted graph.

```bash
./a.out <input file>
```
`input file`: line1: number of vertices, line2: number of edges, line3~n: <vertex> <vertex> <edge weight>.

This will save a `johnson_out.txt` file to the directory.
   
## Merge Inversion:
Counts how many inversions used in a merge sort.

```bash
./a.out
```
`10 numbers`: give an array.

## N-Queen problem:
The classic N-Queen problem.

## Optimal Binary Search Tree:
Computes the optimal binary search tree given probabilities pi and qj.

```bash
./a.out <input file>
```
`input file`: line1: (node 1, probability p1) (node 2, proba...), line2: (dummy keys 0, probability q0) (dummy keys 1, proba...)

This will save a `optimal_bst_out.txt` file to the directory.

## Shannon-Fano coding:
Construct a prefix code based on a set of symbols and their probabilities.

```bash
./a.out
```
`8 elements`: number in sorted order
