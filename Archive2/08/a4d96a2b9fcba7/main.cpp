#include<random>
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d({3, 2, 2, 2});
    d(gen);

    std::vector<int> v(100);
    std::generate(std::begin(v),std::end(v),[&](){return d(gen);});
    
    for(auto i : v)
    {
        std::cout<<i<<"  ";
    }
    std::cout<<std::endl;
}