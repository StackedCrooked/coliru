#include <cstdio>

static char const DOG[9][16] = {{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
                                {'X','D','G','O','O','D','D','O','D','G','O','O','D','D','O','X'},
                                {'X','O','D','O','O','G','G','G','D','O','D','G','O','G','G','X'},
                                {'X','O','G','O','G','D','O','O','D','G','O','O','D','D','D','X'},
                                {'X','D','G','D','O','O','O','G','G','O','O','G','D','G','O','X'},
                                {'X','O','G','D','G','O','G','D','G','O','G','G','O','G','D','X'},
                                {'X','D','D','D','G','D','D','O','D','O','O','G','D','O','O','X'},
                                {'X','O','D','G','O','G','G','D','O','O','G','G','O','O','D','X'},
                                {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'}};

int main()
{
    for (int i = 1; i < 8; i++)
    {
        for (int j = 1; j < 15; j++)
        {
            if (DOG[i][j] == 'D')
            {
                for (int k = i - 1; k < i + 2; k++)
                {
                    for (int l = j - 1; l < j + 2; l++)
                    {
                        if (DOG[k][l] == 'O')
                        {
                            if (DOG[k - (i - k)][l - (j - l)] == 'G')
                            {
                                printf("[%i][%i] = %c, [%i][%i] = %c, [%i][%i] = %c", i, j, DOG[i][j], k, l, DOG[k][l], k - (i - k), l - (j - l), DOG[k - (i - k)][l - (j - l)]);
                            }
                        }
                    }
                }
            }
        }
    }
}