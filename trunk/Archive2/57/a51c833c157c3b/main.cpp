#include <string.h>
#include <stdio.h>
 
int main()
{
    char *tablica[10] = {"repeat 234234", "rdfgdgfeat 234234", "rdfgdgfeat 23;4234","repeat 234234"};
//     if (strstr(tablica[i],"repeat")) continue;
//     
//     if (strchr(tablica[i],';') != NULL) {
//            printf("SEMICOLON");
//    
//        } else {
//            printf("NO SEMICOLON");
//        }
// }
for (int j = 0; j < 10; ++j){
    printf("J %d",j);
        if (strstr(tablica[j],"repeat")) {
        printf("CONTINUE\n");
        continue;
        }
        if (strchr(tablica[j],';') != NULL) {
            printf("SEMICOLON");
    
        } else {
            printf("NO SEMICOLON");
        }
}
}