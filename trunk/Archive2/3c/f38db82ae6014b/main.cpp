#include <iostream>
#include <vector>

template<typename T>
int sizeofvector(const std::vector<T>& myV)
{
    return myV.size();
}

int main()
{
    std::vector<int> a = {1, 2, 3};
    std::vector<double> b = {1.5, 2.7, 5.5, 7.7};
    std::cout << sizeofvector(a) << " " << sizeofvector(b);
}