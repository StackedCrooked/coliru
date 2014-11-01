#include <stdio.h>

int main(){

    printf("This is my first program.\nPlease put in your name...\n");

    char letter[5];


    scanf("%c%c%c%c%c%c", &letter[0], &letter[1], &letter[2], &letter[3], &letter[4], &letter[5]);


    if(letter[0] == 't' && letter[1] == 'r' && letter[2] == 'a' && letter[3] == 'v' && letter[4] == 'i' && letter[5] == 's'){
        printf("Access Granted\nWelcome Travis.\n");
        return 0;
    }



    else{
        printf("You are not autorized.\nThis program will exit now...\n");
        getchar();

    }

    if(letter[0] == 'b' && letter[1] == 'o' && letter[2] == 'b'){
        printf("Access Granted\nWelcome Bob.\n");
        return 0;
    }
}