#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;


int main()
{
    // Initialisation
    std::vector<std::pair<int, int>> values;
    for (int i = 0 ; i <= 10 ; ++i)
    {
        for (int j = 0 ; j <= i ; ++j)
        {
            values.push_back(std::make_pair(i, j));
        }
    }
    
    // Mélanger le tableau
    std::random_shuffle(values.begin(), values.end());
    
    // Récupérer un élément
    std::pair<int, int> val = values.back();
    values.pop_back();
}
