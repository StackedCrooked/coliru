#include <iostream>
#include <vector>

    template <int index>
    struct VectorCache
    {
        template<typename T>
        static std::vector<T>& GetTs()
        {
            static std::vector<T> ts;
            return ts;
        }
    };


int main(){
    VectorCache<1>::GetTs<int>().push_back(1);
    std::cout << VectorCache<1>::GetTs<int>().size() << std::endl;
    std::cout << VectorCache<2>::GetTs<int>().size() << std::endl;
}