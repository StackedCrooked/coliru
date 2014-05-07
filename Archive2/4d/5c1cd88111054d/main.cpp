    // http://stackoverflow.com/questions/23480041/is-the-member-field-order-of-a-class-stable
    #include <iostream>
    #include <algorithm>

    using Int2 = std::array< int, 2 >;
    template <typename T, size_t N> using Matrix = std::array< T, N>;
    
    int main() {
        constexpr int N=5;
        int data[10]= {1,2,7,8,13,14,10,11,4,5};

        auto p = new(reinterpret_cast<void*>(data)) Matrix<Int2, N>;
        
		std::cout << "unsorted" << std::endl;
        int i = 0;
        for(auto & it : *p)
        	std::cout << i++ << ": (" << it[0] << ", " << it[1] << ")" << std::endl;
    	
        std::sort(p->begin(), p->end(), [](const Int2 & a, const Int2 & b) -> bool { return a[0] < b[0]; });

        std::cout << "sorted" << std::endl;
        i = 0;
        for(auto & it : *p)
    		std::cout << i++ << ": (" << it[0] << ", " << it[1] << ")" << std::endl;

    	return 0;
    }
