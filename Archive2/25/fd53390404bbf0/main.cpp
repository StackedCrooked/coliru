#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <iterator>

struct MyStr
{
    int key;
    std::string strval;

    MyStr(int key, const std::string& rStrVal) 
        : key(key)
        , strval(rStrVal) 
    {}

    // let stream operators be friend functions instead of members!
    inline friend std::ostream& operator << (std::ostream& os, const MyStr& val) {
        os << "key[" << val.key << "], strval['" << val.strval << "']";
        return os;
    }

    bool operator < (const MyStr& str) const {
        return (key > str.key);
    }
};

struct comp
{
    bool operator()(int key, MyStr const& m) const { return m.key < key; }
    bool operator()(MyStr const& m, int key) const { return key < m.key; }
};

bool operator==(MyStr const& m1, MyStr const& m2) { return m1.key == m2.key; }

int main()
{
    std::vector <MyStr> testVec = {
        MyStr(4, "key 4"), 
        MyStr(3, "key 3"), 
        MyStr(3, "key 3"), 
        MyStr(2, "key 2"), 
        MyStr(2, "key 2"), 
        MyStr(2, "key 2")
    };

    // sort the vevctor
    std::sort(testVec.begin(), testVec.end());
    
    std::vector<MyStr> unique_keys;
    std::unique_copy(testVec.begin(), testVec.end(), std::back_inserter(unique_keys));
    
    for(auto const& u : unique_keys) {
        std::cout << "Searching for key: " << u.key << '\n';
        auto range = std::equal_range(testVec.begin(), testVec.end(), u.key, comp());
        
        for(auto it = range.first; it != range.second; ++it) {
            std::cout << "key: " << it->key << " value: " << it->strval << '\n';
        }
    }
}
