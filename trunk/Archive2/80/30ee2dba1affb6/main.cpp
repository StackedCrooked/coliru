#include<random>
#include<iostream>

template<typename Type>
struct UniformDistribution
{
    mutable std::mt19937_64 mt_;
    mutable typename std::conditional<std::is_integral<Type>::value
                            , std::uniform_int_distribution<Type>
                            , std::uniform_real_distribution<Type> >::type dist_;    
    Type get() const
    {
        return dist_(mt_);
    }
};

int main()
{
     //produces uniformly distributed integer number in [0, numeric_limist<int>::max()]
     std::cout<<UniformDistribution<int>().get()<<std::endl;

     //produces uniformly distributed double number in [0,1]
     std::cout<<UniformDistribution<double>().get()<<std::endl;
}
    