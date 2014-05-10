#include <chrono>
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
        
        std::vector<foo> extracted_elements(10000);
        const auto start = std::chrono::high_resolution_clock::now();
    
        for (std::size_t i = 0; i < hash_map.size(); ++i) {
            auto it = hash_map.begin();
            std::advance(it, i);
            const auto obj = it->second;
            extracted_elements[i] = obj;
        }
    
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000.0 / 1000.0 / 1000.0;
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
        
        std::vector<foo> extracted_elements(10000);
        const auto start = std::chrono::high_resolution_clock::now();
    
        std::size_t i = 0;
        for (const auto key : keys) {
            extracted_elements[i++] = hash_map[key];
        }
    
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000.0 / 1000.0 / 1000.0;
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
        
        std::vector<foo> extracted_elements(10000);
        const auto start = std::chrono::high_resolution_clock::now();
    
        std::size_t i = 0;
        for (const auto pair : hash_map) {
            extracted_elements[i++] = pair.second;
        }
    
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count() / 1000.0 / 1000.0 / 1000.0;
        std::cout << elapsed << std::endl;
    }
}
