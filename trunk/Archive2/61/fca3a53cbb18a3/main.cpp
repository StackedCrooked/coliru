#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> data_pool;
    data_pool.push_back("Test");
    
    auto lambda = [&data_pool]() -> const std::string&{
        std::size_t index = 0;
        //perform initialization here
        return data_pool[index];
    };
    
    const std::string& constString = lambda();
    std::cout << constString;
    return 0;
}