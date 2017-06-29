#include <stdio.h>
#include <stdlib.h>
int solutions = 0;

int attack (int i, int j, int col, int *hist) {
    if (hist[j] == i)
        return 1;
    if (abs(hist[j] - i) == col - j)
        return 1;
    else
        return 0;
}

void solve (int n, int col, int *hist) {

    if (col == n) {
        solutions++;
        return;
    }
    int i, j;
    for (i=0, j=0; i < n; i++) {
        for (j=0; j < col && !attack(i, j, col, hist); j++);
        if (j < col) continue;

        hist[col] = i;
        solve(n, col+1, hist);
    }
}
int main (int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./a.out <n>\n");
        return -1;
    }
    int n = atoi(argv[1]);

    int hist[n];
    solve(n, 0, hist);
    printf("solutions: %d\n", solutions);
    return 0;
}
