    #include <map>
    #include <iostream>
    
    int main() {
      std::map<int, size_t> m;
      m[0] = m.size();
    
      std::cout << m[0] << std::endl ;
    }