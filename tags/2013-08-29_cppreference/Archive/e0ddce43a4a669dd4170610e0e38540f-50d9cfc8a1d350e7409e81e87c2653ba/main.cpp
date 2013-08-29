    #include <iostream>
    #include <ios>
    #include <algorithm>
    #include <vector>
    #include <string>
    #include <utility>
     
    int main()
    {
        typedef std::string City;

        typedef std::pair<City, int> Element;
        std::vector<Element> v { Element("London", 3), Element("Paris", 9) };
     
        auto int_cmp = [](Element const& lhs, Element const& rhs) {
             return lhs.second < rhs.second;
        };
        
        std::cout << std::boolalpha << std::is_heap(v.begin(), v.end(), int_cmp) << "\n";      
     
        std::make_heap(v.begin(), v.end(), int_cmp);
  
        std::cout << std::boolalpha << std::is_heap(v.begin(), v.end(), int_cmp) << "\n";     
     }