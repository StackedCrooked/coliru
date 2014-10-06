#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    char standards[6][6] = {{"GPRS"}, {"EDGE"}, {"HSDPA"}, {"HSUPA"}, {"HSPA"}, {"LTE"}};
    for(i=0;i<6;i++)
        printf("%s\n",standards[i]);
    return 0;
}