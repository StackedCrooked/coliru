#include <boost/functional/hash.hpp>

#include <unordered_map>
#include <tuple>
#include <vector>
#include <cstdlib>

struct indices
{
    int indexX, indexY, indexZ, indexW;
    
    bool operator==(indices const& other) const
    {
        return std::tie(indexX, indexY, indexZ, indexW) ==
               std::tie(other.indexX, other.indexY, other.indexZ, other.indexW);
    }
};

struct indices_hash
{
    std::size_t operator()(indices const& i) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, i.indexX);
        boost::hash_combine(seed, i.indexY);
        boost::hash_combine(seed, i.indexZ);
        boost::hash_combine(seed, i.indexW);
        
        return seed;
    }
};

int main()
{
    std::unordered_map<indices, std::vector<float>, indices_hash> m;
    m[indices{1,2,3,4}].push_back(42);
}
