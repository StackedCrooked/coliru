#include <stdio.h>
#include <string.h>
 
int istPrimzahl(int iZahl) // 25
{
    int i = 2;
    if(iZahl == 2)
    {
        return 1;
    }
    else
    {
        while(i < iZahl) // 1 ... 25
        {
            if(iZahl % i == 0) // 25 % 5 == 0
            {
                return 0;
            }
            else
            {
                i++;
            }
        }
        return 1;
    }
}

void listePrimzahlzwillinge( int n1, int n2)
{
    int i, j;
    int listePrim[1000];
    for ( i = n1, j = 0; i < n2; i++)
    {
        if(istPrimzahl(i))
        {
            listePrim[j] = i;
            printf("%d\n", i);
            j++;
        }
    }
    for ( i = 0; i < j; i++)
    {
        if (listePrim[i+1] - listePrim[i] == 2)
        {
            printf("zwillinge: %d & %d\n", listePrim[i], listePrim[i+1]);
        }
    }
}
 
int main()
{
  //   printf("%d", istPrimzahl(15));
    listePrimzahlzwillinge( 10, 50);
    return 0;
}