#include <map>
#include <algorithm>

struct Search
{
    bool Manhattan_Distance(std::pair<float, float> const&) {return false;}
    std::map <std::string, std::pair<float,float>> _citymap, _the_cities;
    
    void foo()
    {
        std::copy_if(_citymap.begin(),_citymap.end(),
        std::inserter(_the_cities,_the_cities.end()),[this](auto const& kv_pair) 
            {return Manhattan_Distance(kv_pair.second);});
    }
};

int main() 
{
    Search s;
    s.foo();
}
