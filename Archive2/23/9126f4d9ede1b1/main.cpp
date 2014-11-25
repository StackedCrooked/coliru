#include<vector>
#include<iostream>

template< class ForwardIt1, class ForwardIt2 >
bool has_common_elements( ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last )
{
    auto it=first;
    auto s_it=s_first;
    while(it<last && s_it<s_last)
    {
        if(*it==*s_it)
        {
            return true;
        }

        *it<*s_it ? ++it : ++s_it;
    }
    return false;
}
                          

int main()
{
    std::vector<int> a = {1,2,3,5,8,9,11};
    std::vector<int> b = {11,16,17,18,110};

    //produces uniformly distributed integer number in [0, numeric_limist<int>::max()]
    std::cout<<has_common_elements(a.begin(),a.end(),b.begin(),b.end())<<std::endl;
}
    