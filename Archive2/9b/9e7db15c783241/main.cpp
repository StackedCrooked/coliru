    // http://stackoverflow.com/questions/23480041/is-the-member-field-order-of-a-class-stable
    #include <iostream>
    #include <algorithm>

    template <class T, size_t ROW, size_t COL> using Matrix = std::array<std::array<T, COL>, ROW>;

    int main() {
        constexpr int N=5;
        int data[10]= {1,2,7,8,13,14,10,11,4,5};

        auto p = new(reinterpret_cast<void*>(data)) Matrix<int, N, 2>;
        
		std::cout << "unsorted" << std::endl;
        int i = 0;
        for(auto & it : *p)
        	std::cout << i++ << ": (" << it[0] << ", " << it[1] << ")" << std::endl;
    	
        std::sort(p->begin(), p->end());
 
        std::cout << "sorted" << std::endl;
        i = 0;
        for(auto & it : *p)
    		std::cout << i++ << ": (" << it[0] << ", " << it[1] << ")" << std::endl;

    	return 0;
    }
