#include<stdio.h>
#include<stdlib.h>
int main(){
    int *x, *y, n, m, i;

    printf("Enter lenght of arrays x and y (separated by space): ");
    scanf("%d%d", &n, &m); fflush(stdin);

    if (x = (int*)malloc(sizeof(int) * n) == NULL){
        fprintf(stderr, "Error!\n");
        exit(1);
    }
    if (y = (int*)malloc(sizeof(int) * m) == NULL){
        fprintf(stderr, "Error!\n");
        exit(1);
    }

    printf("Enter %d values for X array (separated by space) ", n);
    for (i = 0; i < n; i++)
        scanf("%d", x + i);
    fflush(stdin);

    printf("Enter %d values for Y array (separated by space): ", m);
    for (i = 0; i < m; i++)
        scanf("%d", y + i);
    } //the two for's were originally in a function, I tried using the code like this as well
    return 0;
}