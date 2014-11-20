#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>

template <class iterator>
class IndexComparison
{
public:
    IndexComparison (iterator const& _begin, iterator const& _end) :
      begin (_begin),
      end (_end)
    {}
    
    bool operator()(size_t a, size_t b) const
    {
        return *std::next(begin,a) < *std::next(begin,b);
    }

private:
    const iterator begin;
    const iterator end;
};

int main()
{

    std::vector<char> values{'e','b','d','c','a'};
    std::vector<size_t> indices(values.size());
    std::iota(indices.begin(),indices.end(),0);

    std::cout<<"original pair:"<<std::endl;
    for(auto i : indices)
        std::cout<<i<<" ";
    std::cout<<std::endl;
    for(auto v : values)
        std::cout<<v<<" ";
    std::cout<<"\n"<<std::endl;

    std::sort(indices.begin(),indices.end(), IndexComparison<decltype(values.cbegin())>(values.cbegin(),values.cend()));
    //std::sort(values.begin(),values.end());

    auto temp=values;
    for(size_t i=0;i<indices.size();++i)
    {
         values[i]=temp[indices[i]];
    }

    std::cout<<"sorted pair:"<<std::endl;
    for(auto i : indices)
        std::cout<<i<<" ";
    std::cout<<std::endl;
    for(auto v : values)
        std::cout<<v<<" ";
    std::cout<<std::endl;
}