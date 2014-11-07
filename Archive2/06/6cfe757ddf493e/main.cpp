#include <stdio.h>;

main() {

    char fajl[10];
    char szoveg[1000];
    
    printf("Ird be a szovegfajl nevet:\n");
    scanf("%s",fajl);
    FILE *f;
    f = fopen(fajl, "r+");

    fscanf(f, "%s", szoveg);

    printf("%s tartalma:\n",fajl);
    printf("%s", szoveg);

}