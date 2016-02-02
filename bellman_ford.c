#include <stdio.h>

#define INF 1000000
typedef struct {
    int u, v, w;
} Edge;

int n_nodes=0, n_edges=0;
int d[32];
Edge e[1024];

void bellman_ford(int s) {
    int i, j;

    for (i=0; i<n_nodes; i++)
        d[i] = INF;

    d[s] = 0;

    for (i=0; i<n_nodes-1; i++)
        for (j=0; j<n_edges; j++)
            if (d[e[j].u] + e[j].w < d[e[j].v])
                d[e[j].v] = e[j].w + d[e[j].u];

}

int main(int argc, char** argv) {
    if (argc!=3) {
        printf("usage: ./a.out <filename> <source>\n");
        return;
    }
    int i, j, w, source;
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen("bellman_ford_out.txt", "w");
    source = atoi(argv[2]) - 1;
    fscanf(in, "%d", &n_nodes);

    for (i=0; i<n_nodes; i++)
        for (j=0; j<n_nodes; j++) {
            fscanf(in, "%d", &w);
            if (w!=0) {
                e[n_edges].u = i;
                e[n_edges].v = j;
                e[n_edges].w = w;
                n_edges++;
            }
        }

    bellman_ford(source);

    fprintf(out, "Distances from source %d\n\n", source+1);
    for (i=0; i<n_nodes; i++)
        fprintf(out, "to node %d: %d\n", i+1, d[i]);
    fprintf(out, "\n");

    fclose(in);
    fclose(out);
}
