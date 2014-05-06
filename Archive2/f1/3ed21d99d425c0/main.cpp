    #include <iostream>
    #include <algorithm>
    
    typedef std::array<int,2> Pair;

    int main() {
    	int N=5;
    	int data[10]= {1,2,7,8,13,14,10,11,4,5};
        Pair* p = reinterpret_cast< Pair* >( data );
    	
	    std::cout << "unsorted" << std::endl;
    	for(int i=0; i<N; ++i)
    		std::cout << i << ": (" << p[i][0] << ", " << p[i][1] << ")" << std::endl;
    	
	    std::sort(p, p+N);
 
	    std::cout << "sorted" << std::endl;
        for(int i=0; i<N; ++i)
    		std::cout << i << ": (" << p[i][0] << ", " << p[i][1] << ")" << std::endl;

    	return 0;
    }

