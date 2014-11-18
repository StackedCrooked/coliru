#include<algorithm>
#include<numeric>
#include<iostream>
#include<iomanip>
#include<vector>

template<class InputIt>
InputIt repetition_find(InputIt first, InputIt last, size_t repetitions)
{
    std::vector<int> temp;
    std::adjacent_difference(first, last, std::back_inserter(temp));
    temp.front()=0;
    
    int count=0;
    std::for_each(temp.rbegin(), temp.rend(), [&](auto& a) { if(a==0) a = ++count; else {a=++count; count=0;}} );
    
    auto diff =  std::find_if(temp.begin(), temp.end(), [&](auto a) {return a>=repetitions;} ) - temp.begin();
    return std::next(first, diff);
}


int main()
{
    std::vector<int> values = { 9, 9, 8, 8, 8, 8, 7, 7, 6, 6, 6 };

    for(auto v : values)
    {
        std::cout<<std::setw(3)<<v<<" ";
    }
    std::cout<<std::endl;


    std::vector<int> temp;
    std::adjacent_difference(values.begin(), values.end(),std::back_inserter(temp));
    temp.front()=0;

    for(auto v : temp)
    {
        std::cout<<std::setw(3)<<v<<" ";
    }
    std::cout<<std::endl;

    int count=0;
    std::for_each(temp.rbegin(), temp.rend(), [&](auto& a) { if(a==0) a = ++count; else {a=++count; count=0;}} );

    for(auto v : temp)
    {
        std::cout<<std::setw(3)<<v<<" ";
    }
    std::cout<<std::endl;

    std::cout<<*repetition_find(values.begin(), values.end(), 4)<<std::endl;
}
