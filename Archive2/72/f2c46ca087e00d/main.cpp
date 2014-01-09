    #include <boost/range/irange.hpp>
    #include <iostream>
    
    int main()
    {
        for(auto i : boost::irange(0, 256) )
            std::cout << i << "\n";
        return 0;
    }