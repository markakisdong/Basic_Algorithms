#include <stdio.h>
#include <string.h>
/*
node[0].frequency = 108732;
node[1].frequency = 108128;
node[2].frequency = 93156;
node[3].frequency = 80369;
node[4].frequency = 75780;
node[5].frequency = 53246;
node[6].frequency = 51438;
node[7].frequency = 36651;
*/

typedef struct characters{
    char encode[10];
    int frequency;
}chs;

void shannon (int start, int end, chs* arr) {
    int i = start;
    int j = end;
    int k;
    int isum = arr[i].frequency;
    int jsum = arr[j].frequency;

    while (i < (j-1)) {
        while (isum > jsum && i < (j-1)) {
            j--;
            jsum += arr[j].frequency;
        }
        while (isum < jsum && i < (j-1)) {
            i++;
            isum += arr[i].frequency;
        }
    }

    if (i == start) {
        strcat(arr[start].encode, "0");
    } else if ((i - start) >= 1) {
        for (k=start; k <= i; k++)
            strcat(arr[k].encode, "0");

        shannon(start, i, arr);
    }
    
    if (j == end) {
        strcat(arr[end].encode, "1");
    } else if ((end - j) >= 1) {
        for(k=j; k <= end; k++)
            strcat(arr[k].encode, "1");

        shannon(j, end, arr);
    }
}

int main (int argc, char** argv) {
    if (argc != 1) {
        printf("too many arguments.\n");
        return -1;
    }
    chs node[8];
    int n=8, i, j;
    printf("Your eight element in sorted order:\n");
    for (i=0; i < 8; i++) {
        printf("element %d: ", i+1);
        scanf("%d", &node[i].frequency);
    }

    for (i=0; i < 8; i++)
        for (j=0; j < 10; j++)
            node[i].encode[j] = 0;
    
    shannon(0, n-1, node);

    // Print the data and code 
    for(i=0; i < 8; i++) {
        printf("%7d: ", node[i].frequency);
        printf("%s\n", node[i].encode);
    }
    return 0;
}
