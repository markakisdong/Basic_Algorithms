#include <stdio.h>
int arr[10];

int merge (int A[], int p, int q, int r) {
    int i, j, k, inversions = 0;

    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1];
    int R[n2];

    for (i=0; i < n1; i++)
        L[i] = A[p+i];
    for (j=0; j < n2; j++)
        R[j] = A[q+j+1];

    for (i=0, j=0, k=p; k <= r; k++) {
        if (i == n1)
            A[k] = R[j++];
        else if (j == n2)
            A[k] = L[i++];
        else if (L[i] <= R[j])
            A[k] = L[i++];
        else {
            A[k] = R[j++];
            inversions += n1 - i;
        }
    }

    return inversions;
}
int merge_sort (int A[], int p, int r) {

    int inversions = 0;
    if (p < r) {
        int q = (p + r)/2;
        inversions += merge_sort(A, p, q);
        inversions += merge_sort(A, q+1, r);
        inversions += merge(A, p, q, r);
    }

    return inversions;
}
int main(void) {
    int i;
    printf("merge-sort and inversions.\n10 numbers:\n");
    for (i=0; i < 10; i++)
        scanf("%d", &arr[i]);

    int inversions = merge_sort(arr, 0, 9);
    printf("Sorting complete: ");
    for (i=0; i < 10; i++)
        printf("%d ", arr[i]);
    printf("\ninversions: %d\n", inversions);

    return 0;
}
