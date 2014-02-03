#include <iostream>

struct Cell {};

template<size_t M, size_t N>
class MapV2
{

public:
    MapV2();
    ~MapV2();
    int m = M;
    int n = N;
private:
    Cell myMapV2[M*N];
};

template<size_t M, size_t N>
MapV2<M, N>::MapV2()
{

}

template<size_t M, size_t N>
MapV2<M, N>::~MapV2()
{

}

template class MapV2<size_t, size_t>;

int main()
{
    const size_t xLength = 6;
    const size_t yLength = 8;
    MapV2 <xLength, yLength> Example;
    std::cout << Example.m << " " << Example.n;
    return 0;
}