#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <unordered_map>

struct foo {
    uint64_t category;
    uint64_t id;
};

int main () {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 100*1000);
    {
        std::unordered_map<uint64_t, foo> hash_map;
        for (int i = 10000; i > 0; --i) {
            hash_map[dist(rng)] = foo{rng(), rng()};
        }
        std::cout << hash_map.size() << std::endl;
        std::vector<uint64_t> vec;
        for (auto & elem : hash_map) {
            vec.emplace_back(elem.first);
        }
        
        std::vector<foo> extracted_elements(hash_map.size());
        const auto start = std::chrono::high_resolution_clock::now();
    
        for (std::size_t i = 0; i < hash_map.size(); ++i) {
            extracted_elements[i] = hash_map[vec[i]];
        }
    
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000.0 / 1000.0;
        std::cout << elapsed << std::endl;
    }
    {
        std::unordered_map<uint64_t, foo> hash_map;
        std::vector<uint64_t> keys;
        for (int i = 10000; i > 0; --i) {
            const auto key = dist(rng);
            if (hash_map.find(key) == std::end(hash_map)) {
                keys.emplace_back(key);
                hash_map[key] = foo{rng(), rng()};
            }
        }
        std::cout << hash_map.size() << std::endl;
        std::vector<std::reference_wrapper<foo>> vec;
        for (auto & elem : hash_map) {
            vec.emplace_back(elem.second);
        }
        
        std::vector<foo> extracted_elements(hash_map.size());
        const auto start = std::chrono::high_resolution_clock::now();
    
        for (std::size_t i = 0; i < hash_map.size(); ++i) {
            extracted_elements[i] = vec[i];
        }
    
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000.0 / 1000.0;
        std::cout << elapsed << std::endl;
    }
}
