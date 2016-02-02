#include <stdio.h>
#include <stdlib.h>
double e[100][100] = {0}, w[100][100] = {0}, root[100][100] = {0};

struct node {
    int left, right;
}node[100];

int traverse (int l, int r) {
    int p = root[l][r];
    if (l<=r) {
        node[p].left = traverse(l, p-1);
        node[p].right = traverse(p+1, r);
    }
    return p;
}

void Optimal_BST (double p[], double q[], int n) {
    int i, j, l, r;
    double t;
    for (i=1; i<=n+1; i++) {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }

    for (l=1; l<=n; l++) {
        for (i=1; i<=n-l+1; i++) {
            j = i+l-1;
            e[i][j] = 1000;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            for (r=i; r<=j; r++) {
                t = e[i][r-1]+e[r+1][j]+w[i][j];
                if (t<e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

int main (int argc, char** argv) {
    if (argc!=2) {
        printf("usage: ./a.out <filename>\n");
        return;
    }
    FILE *in, *out;
    double p[20]={0}, q[20]={0};
    char lq, kc, n, comma, rq, sp;
    int i, j, k, l;

    in = fopen(argv[1], "r");
    out = fopen("optimal_bst_out.txt", "w");

    i = 1;
    do {
        fscanf(in, "%c%c%c%c%lf%c%c", &lq, &kc, &n, &comma, &p[i++], &rq, &sp);
        //puts("00");
    } while (sp!='\r' && sp!='\n');

    j = 0;
    fscanf(in, "%c", &lq);
    do {
        fscanf(in, "%c%c%c%c%lf%c%c", &lq, &kc, &n, &comma, &q[j++], &rq, &sp);
    } while (sp!='\r' && sp!='\n');
    //printf("i=%d, j=%d\n", i, j);

    Optimal_BST(p, q, i-1);
    traverse(1, i-1);

    for (k=1; k<i; k++) {
        fprintf(out, "(k%d,", k);
        if (node[k].left==0)
            fprintf(out, "d%d,", l++);
        else
            fprintf(out, "k%d,", node[k].left);
        if (node[k].right==0)
            fprintf(out, "d%d", l++);
        else
            fprintf(out, "k%d", node[k].right);
        fprintf(out, ") ");
    }
    
    fprintf(out, "\ncost: %.3lf\n", e[1][i-1]);

    /*
    for (k=0; k<=i; k++) {
        for (l=0; l<i; l++)
            fprintf(stdout, "%.3lf ", root[k][l]);
        puts("");
    }
    */    

    fclose(in);
    fclose(out);
    return 0;
}
