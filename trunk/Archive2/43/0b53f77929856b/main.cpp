#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

typedef std::string Option;
typedef std::map<std::string, Option> OptionsMap;
typedef std::vector<Option> InsertionOrder;

class OptionsMapWithInsertionOrder
:
    public OptionsMap // yes, inheritance abuse, sue me
{
public:
    Option& operator[](std::string const& key)
    {
        OptionsMap::iterator opt = find(key);
        if (opt != end()) {             // key already present in map
            InsertionOrder::iterator in = std::find(v_.begin(), v_.end(), key);
            assert(in != v_.end());     // key should also be present in v_ 
            std::swap(*in, v_.back());  // key now at the back
            return opt->second;            
        } else {                        // key not present in map yet
            assert(std::find(v_.begin(), v_.end(), key) == v_.end());
            v_.push_back(key);
            
            // C++98 mandates this 
            return (insert(std::make_pair(key, Option())).first)->second;
        }
    }
    
    friend std::ostream& operator<<(std::ostream&, OptionsMapWithInsertionOrder const&);
    
private:
    InsertionOrder v_;    
};

std::ostream& operator<<(std::ostream& os, OptionsMapWithInsertionOrder const& m)
{
    for (std::size_t i = 0; i < m.v_.size(); ++i) {
          std::string const& key = m.v_[i];
          os << key << ": " << m.find(key)->second << "\n";
    }
    return os;
}

int main()
{
    OptionsMapWithInsertionOrder m;
    m["foo"] = "bar";
    m["meh"] = "huh";
    
    std::cout << m << "\n";
    
    m["foo"] = "duh";
    
    std::cout << m << "\n";
    
    m["meh"] = "yo!";
    
    std::cout << m << "\n";
}
