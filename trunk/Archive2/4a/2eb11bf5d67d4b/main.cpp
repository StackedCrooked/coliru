#include <stdio.h>

int main()
{
    int matriz1[50][50];
    int matriz2[50][50];
    
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            matriz1[i][j] = i + j;
        }
    }
    
    printf("Valores da matriz A\n");
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            printf("%d ", matriz1[i][j]);
        }
        printf("\n");
    }
    
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            if(i == j){
                matriz2[i][j] = matriz1[i][j] * 3;
            }
            else{
                matriz2[i][j] = matriz1[i][j] * 2;
            }
        }
    }
    

    printf("\nValores da matriz B\n");
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            printf("%d ", matriz2[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
