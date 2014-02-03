#include <string>
#include <sstream>
#include <iostream>
#include <cassert>
    
        
    int main(int argc, char* argv[])
    {
        const int size = 1000000;
        
        std::stringstream ss;
        std::cout << ss.rdbuf()->in_avail() << std::endl;
        for(unsigned int i = 0; i<size; ++i)
        {
            ss << "A";
        }
        ss.seekp(0, std::ios_base::beg);
        ss.seekg(0, std::ios_base::beg);
        
        // Test 1: Ensure size is what we put in
        std::cout << ss.rdbuf()->in_avail() << std::endl;
        assert(ss.rdbuf()->in_avail() == size);
        
        // Test 2: Ensure # bytes available at end is 0
        ss.seekg(0, std::ios_base::end);
        assert(ss.rdbuf()->in_avail() == 0);

         // Reset object
        ss.str("");
        // Test 3: Ensure no bytes available at beginning
        ss.seekg(0, std::ios_base::beg);
        std::cout << ss.rdbuf()->in_avail() << std::endl;
        assert(ss.rdbuf()->in_avail() == 0);

    
        return EXIT_SUCCESS;
    }

    
    
    
    
    