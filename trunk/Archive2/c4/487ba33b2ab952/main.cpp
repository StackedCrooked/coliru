#include <iostream>

struct pair
{
    int first;
    int second;
};

int main()
{

    // Initilisation
    pair values[66];
    size_t index = 0;
    for (int i = 0 ; i <= 10 ; ++i)
    {
        for (int j = 0 ; j <= i ; ++j)
        {
            pair tmp = { i, j };
            values[index] = tmp;
            ++index;
        }
    }
    
    // Mélanger le tableau
    // Débrouille-toi
    
    // Pour chaque opération
    pair val = values[index];
    int res = val.first * val.second;
    --index;
}
