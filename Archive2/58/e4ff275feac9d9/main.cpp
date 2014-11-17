#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <map>

const size_t MAX_ENTRIES = 100000;
const size_t MAX_FIELD = 100;

struct some {
    some() {
        field_.resize(MAX_FIELD);
        for(auto& s: field_)
            s = "abcdefgh";
    }
    std::vector<std::string> field_;
};

int main() {
    std::vector<some> v(MAX_ENTRIES);
    v[MAX_ENTRIES - 1].field_[MAX_FIELD - 1] = "abcde";
    {
        auto start = std::chrono::system_clock::now();
        std::cout << "Starting vector test...\n";
        auto it = std::find_if(v.begin(), v.end(),
            [](const some& s) {
                if(std::find_if(s.field_.begin(), s.field_.end(),
                                            [](const std::string& str) {
                                                return str == "abcde";
                                            }) != s.field_.end())
                    return true;
                else
                    return false;
            });
        std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - start;
        if(it != v.end())
            std::cout << "Found\n";
        else
            std::cout << "Not found\n";
        std::cout << "Elapsed: " << elapsed.count() 
                  << "s" << std::endl << std::endl;
    }
    
    std::map<int, std::string> m;
    for(size_t i = 0; i < MAX_ENTRIES-1; ++i) {
        m.insert(std::make_pair(i, "abcdefgh"));
    }
    m.insert(std::make_pair(MAX_ENTRIES, "abcde"));
    {
        auto start = std::chrono::system_clock::now();
        std::cout << "Starting map test...\n";
        auto it = m.find(468);
        std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - start;
        if(it != m.end())
            std::cout << "Found\n";
        else
            std::cout << "Not found\n";
        std::cout << "Elapsed: " << elapsed.count() 
                  << "s" << std::endl;
    }
    
}
