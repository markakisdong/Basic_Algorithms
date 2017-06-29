#include <stdio.h>
#include <stdlib.h>

#define NINF -99999999
#define INF 99999999
typedef struct {
    int u, v, w;
} Edge;

int g[100][100], result[100][100];
Edge e[100];
int N, E, E_bf;

void union_edge () {
    int i, j;
    for (i=0; i < N; i++) {
        g[N][i] = 0;
        e[E_bf].u = N;
        e[E_bf].v = i;
        e[E_bf++].w = 0;
    }
}

int* bellman_ford (int s) {
    int i, j;
    int *d = malloc(sizeof(int)*(N+1));

    for (i=0; i <= N; i++)
        d[i] = INF;

    d[s] = 0;

    for (i=0; i <= N-1; i++)
        for (j=0; j < E_bf; j++)
            if (d[e[j].u] + e[j].w < d[e[j].v])
                d[e[j].v] = e[j].w + d[e[j].u];

    for (i=0; i < E_bf; i++)
        if (d[e[i].u] + e[i].w < d[e[i].v])
            d[0] = NINF;

    return d;
}

int* dijkstra (int s) {
    int i, k;
    int *d = malloc(sizeof(int)*N);
    int visited[N];
    int parent[N];
    for (i=0; i < N; i++) {
        d[i] = INF;
        visited[i] = 0;
    }
    d[s] = 0;
    parent[s] = s;
    for (k=0; k < N; k++) {
        int a=-1, b=-1, min=INF;
        for (i=0; i < N; i++)
            if (!visited[i] && d[i] < min) {
                a = i;
                min = d[i];
            }

        if (a == -1) break;
        visited[a] = 1;

        for (b=0; b < N; b++)
            if (!visited[b] && d[a] + g[a][b] < d[b]) {
                d[b] = d[a] + g[a][b];
                parent[b] = a;
            }
    }
    return d;
}

int johnson () {
    int i, j;
    int *h, *allpairssp;
    /* first add a zero cost edge to each vertex */
    union_edge();
    /* second do bellman ford and check negative cycle */
    h = bellman_ford(N);
    if (h[0] == NINF)
        return 0;
    /* third re-weight each edge */
    /*
       for (i=0; i<N; i++) {
       for (j=0; j<N; j++)
       printf("%d ", g[i][j]);
       printf("\n");
       }
       */
    for (i=0; i < E; i++) {
        e[i].w += h[e[i].u] - h[e[i].v];
        g[e[i].u][e[i].v] += h[e[i].u] - h[e[i].v];
    }
    /* fourth run dijkstra */
    for (i=0; i < N; i++) {
        allpairssp = dijkstra(i);
        for (j=0; j < N; j++)
            if (allpairssp[j] != INF)
                allpairssp[j] += h[j] - h[i];
        /*
           for (j=0; j<N; j++)
           printf("%d ", allpairssp[j]);
           printf("\n");
           */
        for (j=0; j < N; j++)
            result[i][j] = allpairssp[j];
    }
    return 1;
}

int main (int argc, char** argv) {
    if (argc != 2) {
        printf("usage: ./a.out <filename>\n");
        return;
    }
    int i, j;
    FILE *in, *out;
    in = fopen(argv[1], "r");
    out = fopen("johnson_out.txt", "w");
    fscanf(in, "%d", &N);
    fscanf(in, "%d", &E);
    E_bf = E;
    for (i=0; i <= N; i++)
        for (j=0; j <= N; j++) {
            g[i][j] = INF;
            //g[i][i] = 0;
        }

    for (i=0; i < E; i++) {
        int u, v, w;
        fscanf(in, "%d %d %d", &u, &v, &w);
        e[i].u = u-1;
        e[i].v = v-1;
        e[i].w = w;
        g[u-1][v-1] = w;
    }

    if (!johnson())
        fprintf(out, "the graph has negative cycles\n");
    else {
        for (i=0; i < N; i++)
            for (j=0; j < N; j++) {
                if (result[i][j]!=INF)
                    fprintf(out, "%d %d: %d\n", i+1, j+1, result[i][j]);
                else
                    fprintf(out, "%d %d: INF\n", i+1, j+1);
            }
    }
    fclose(in);
    fclose(out);
    return 0;
}
