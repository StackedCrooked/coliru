#include <vector>
#include <iostream>

std::vector<std::vector<double> > vect = {
    {1, 2, 3},
    {4, 5, 6}, 
    {7, 8, 9}
};

template<typename Inverse>
void Diag(Inverse begin, Inverse end)
{
    for(auto it = begin; it != end; ++it)
        for(auto& col : *it)
            std::cout << col << ' ';
}

int main()
{
    Diag(std::begin(vect), std::end(vect));
}
