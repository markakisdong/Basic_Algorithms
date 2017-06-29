#include <stdio.h>
#include <time.h>
#define MIN_INT -10000000
#define MAX_INT 10000000

typedef struct {
    int left, right, sum;
} max_subarr;
int n = 46;

max_subarr find_max_cross (int A[], int left, int mid, int right) {
    max_subarr rst = {0, 0, MIN_INT};
    int i, j;
    int left_sum = MIN_INT;
    int sum = 0;
    
    for (i=mid-1; i >= left; i--) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            rst.left = i;
        }
    }

    int right_sum = MIN_INT;
    sum = 0;
    for (j=mid; j < right; j++) {
        sum += A[j];
        if (sum > right_sum) {
            right_sum = sum;
            rst.right = j;
        }
    }

    rst.sum = left_sum + right_sum;
    return rst;
}

max_subarr find_max_sub (int A[], int left, int right) {
    if (left+1 == right) {
        max_subarr rst = {left, right, A[left]};
        return rst;
    } else {
        int mid = (left + right)/2;
        max_subarr arr_left = find_max_sub(A, left, mid);
        max_subarr arr_right = find_max_sub(A, mid, right);
        max_subarr arr_cross = find_max_cross(A, left, mid, right);

        if (arr_left.sum >= arr_right.sum && arr_left.sum >= arr_cross.sum)
            return arr_left;
        else if (arr_right.sum >= arr_left.sum && arr_right.sum >= arr_cross.sum)
            return arr_right;
        else
            return arr_cross;
    }
}

max_subarr find_max_bf (int A[], int left, int right) {
    
    int i, j;
    max_subarr rst = {0, 0, MIN_INT};
    
    for (i=left; i < right; i++) {
        int sum = 0;
        for (j=i; j < right; j++) {
            sum += A[j];
            //printf("sum = %d\n", sum);
            if (sum > rst.sum) {
                rst.left = i;
                rst.right = j;
                rst.sum = sum;
            }
        }
    }

    return rst;
}

max_subarr find_max_mix (int A[], int left, int right) {
    if (right - left < n) {
        return find_max_bf(A, left, right);
    } else {
        int mid = (left + right)/2;
        max_subarr arr_left = find_max_mix(A, left, mid);
        max_subarr arr_right = find_max_mix(A, mid, right);
        max_subarr arr_cross = find_max_cross(A, left, mid, right);

        if (arr_left.sum >= arr_right.sum && arr_left.sum >= arr_cross.sum)
            return arr_left;
        else if (arr_right.sum >= arr_left.sum && arr_right.sum >= arr_cross.sum)
            return arr_right;
        else
            return arr_cross;
    }
}

int main (void) {
    int type, e, i, l, r;
    int arr[1000000] = {0};
    for (i=0; i < 1000000; i++) {
        arr[i] = rand() % 201 - 100;
        if (arr[i] == 0) arr[i] = 1;
    }

    printf("elements: ");
    scanf("%d", &e);

    printf("==========================\n");

    // use build-in functions to record time.
    clock_t start, stop;
    double time_brute, time_rc, time_mix;

    start = clock();
    max_subarr brute_force = find_max_bf(arr, 0, e-1);
    stop = clock();

    time_brute = ((double)(stop - start))/CLOCKS_PER_SEC;


    printf("brute-force-time: %lf\n", time_brute);

    start = clock();
    max_subarr recursion = find_max_sub(arr, 0, e-1);
    stop = clock();

    time_rc = ((double)(stop - start))/CLOCKS_PER_SEC;

    start = clock();
    max_subarr mix = find_max_mix(arr, 0, e-1);
    stop = clock();

    time_mix = ((double)(stop - start))/CLOCKS_PER_SEC;

    printf("==========================\nrecursion-time:   %lf\n", time_rc);
    printf("==========================\nmix-time:         %lf\n", time_mix);
    printf("==========================\nb-f-l: %d, r: %d, sum: %d\n", brute_force.left, brute_force.right, brute_force.sum);
    printf("r-c-l: %d, r: %d, sum: %d\n", recursion.left, recursion.right, recursion.sum);
    printf("m-c-l: %d, r: %d, sum: %d\n", mix.left, mix.right, mix.sum);

    return 0;
}
