#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <boost/algorithm/string/find.hpp>

struct Object
{
    Object(int i) : i_(i) {}
    int get() const { return i_; }
    Object& operator*=(int m)
    {
        i_ *= m;
        return *this;
    }
    
    int i_;
};

bool operator==(Object const& l, Object const& r)
{
    return l.get() == r.get();
}

int main()
{
    std::vector<Object> v1{1,2,3,4,5,6,7,8,9, 
                           1,2,3,4,5,6,7,8,9,
                           1,2,3,4,5,6,7,8,9};
    std::vector<Object> v2{4,5,6};

    // find if the larger vector contains the smaller one
    auto result = boost::find_nth(v1, v2, 1);
    if(not result.empty()) {
        // apply function to each sub-range element
        std::for_each(result.begin(), result.end(), [](Object &o) { o *= 2; });
    }

    for(auto const& v : v1) {
        std::cout << v.get() << ' ';
    }
    std::cout << '\n';
}
