    #include <unordered_map>
    #include <iostream>
    
    int main() {
      std::unordered_map<int, size_t> um;
      um[0] = um.size();
    
      std::cout << um[0] << std::endl ;
    }