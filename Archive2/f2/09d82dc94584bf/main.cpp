
#include <iostream>
#include <iomanip>

#include <cstring>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

//typedef std::string substring;
struct substring {
    const char* data;
    size_t len;
    //size_t hash;
    
    inline size_t size() const { return len; }
    
    inline bool operator==(const substring& that) const {
        if(len != that.len) return false;
        return !std::memcmp(data, that.data, len);
    }
    
    size_t calc_hash() const {    
        unsigned long h = 7;
        for (int i = 0; i < len; ++i)
            h = 31 * h + data[i];
        return (size_t)h;
    }
    
    operator std::string() const {
        return std::string{ data, len };
    }
};

namespace std {
template<>
struct hash<substring> {
    inline size_t operator()(const substring& ss) const {
        return ss.calc_hash();
    }
};
}

struct static_string {
    char data[100];
    size_t len;
    
    inline size_t size() const {
        return len;
    }
    
    inline char& operator[](size_t ix) {
        return data[ix];
    }
};

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::string> input(n);
    size_t maxlen = 0;
    for(auto&& r : input) {
        std::cin >> r;
    }
    std::unordered_set<short> idx;
    for(short i = 0; i < n; ++i) idx.insert(i);
    
    std::unordered_map<short, substring> result;

    for(size_t sublen = 1; sublen < 100; ++sublen) {
        std::unordered_map<substring, short> subs;
        subs.reserve(255*sublen);
        for(short index = 0; index < n; ++index) {
            auto&& r = input[index];
            if(r.size() < sublen) continue;
            
            for(int i = 0; i <= r.size()-sublen; ++i) {
                substring ss{ r.data() + i, sublen };
                std::cout << r << "[" << i << "]" << std::endl;
                std::cout << std::string(ss) << std::endl;
                
                auto it = subs.find(ss);
                if(it != subs.end()) {
                    if(it->second != index) it->second = -1;
                } else subs[ss] = index;
            }
        }
        for(auto&& mapping: subs) if(mapping.second != -1) {
            idx.erase(mapping.second);
            auto it = result.find(mapping.second);
            if(it == result.end()) result[mapping.second] = mapping.first;
            if(idx.empty()) goto end;
        }
    }
    
end:
    for(short s = 0; s < input.size(); ++s) {
        std::cout << std::string(result[s]) << std::endl;
    }
}
