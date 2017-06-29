#include <stdio.h>
#include <time.h>

typedef struct {
    int left, right, sum;
} max_subarr;
int small[100000];
int medium[1000000];
int large[10000000];

max_subarr find_max_linear (int A[], int left, int right) {
    
    max_subarr rst = {left, left, A[left]};
    int tmp_sum = A[left];
    int tmp_left = left;
    int i;

    for (i=left+1; i < right; i++) {
        tmp_sum += A[i];
        if (tmp_sum > rst.sum) {
            rst.sum = tmp_sum;
            rst.left = tmp_left;
            rst.right = i;
        }
        if (tmp_sum < 0) {
            tmp_left = i+1;
            tmp_sum = 0;
        }
    }

    return rst;
}

int main (void) {
    int i, e, f;
    for (i=0; i < 100000; i++) {
        small[i] = rand() % 201 - 100;
        if (small[i] == 0) small[i] = 1;
    }
    for (i=0; i < 1000000; i++) {
        medium[i] = rand() % 201 - 100;
        if (medium[i] == 0) medium[i] = 1;
    }
    for (i=0; i < 10000000; i++) {
        large[i] = rand() % 201 - 100;
        if (large[i] == 0) large[i] = 1;
    }

    printf("small(1), medium(2), large(3)? ");
    scanf("%d", &f);

    //printf("elements: ");
    //scanf("%d", &e);
    printf("======================\n");

    clock_t start, stop;
    double time_linear;

    start = clock();
    max_subarr linear;
    if (f == 1)
        linear = find_max_linear(small, 0, 100000-1);
    else if (f == 2)
        linear = find_max_linear(medium, 0, 1000000-1);
    else
        linear = find_max_linear(large, 0, 10000000-1);

    stop = clock();

    time_linear = ((double)(stop - start))/CLOCKS_PER_SEC;

    printf("linear-time: %lf\n", time_linear);
    printf("=======================\nli-l: %d, li-r: %d, li-sum: %d\n", linear.left, linear.right, linear.sum);
    // printf("linear-time: %lf\nmax-sub-l: %d, r: %d, sum: %d\n", time_linear, linear.left, linear.right, linear.sum);
    return 0;
}
