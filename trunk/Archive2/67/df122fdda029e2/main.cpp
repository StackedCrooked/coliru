#include <stdio.h>

char acids[24] = {'A','R','N','D','C','Q','E','G','H','I','L','K','M','F','P','S','T','W','Y','V','B','Z','X','-'};

int main()
{
    acids[17] = '%';
    for(int i = 0; i < 25; ++i) {
        //char tmp = acids[i];
        //tmp += 1;
        printf("%c\n", acids[i]);   
    }
}
