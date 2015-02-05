#include <unordered_map>
#include <vector>

#include <boost/functional/hash.hpp>

using namespace std;

template <typename Container> 
struct container_hash {
    std::size_t operator()(Container const& c) const {
        return boost::hash_range(c.begin(), c.end());
    }
};

int main()
{
    unordered_map<vector<int>, int, container_hash<vector<int>>> hash;
    
    hash[{1,2,3,4}] = 1;
    hash[{5,6,7,8}] = 2;
}
