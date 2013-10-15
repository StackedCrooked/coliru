#include <iostream>

// You need this:
template<int N, int M, int K>
class A;

template<int N, int M>
class GCD{
public:
    // as it is used here
    static const int a=A<N,M,N%M>::a;
};

template<int N, int M, int K>
class A{
public:
    static const int a=A<M,K,M%K>::a;
};

template<int N, int M>
class A<N,M,0>{
public:
    static const int a=M;
};

int main()
{
    std::cout << GCD<11,13>::a;
    return 0;
}
