    #include <iostream>
    #include <algorithm>
    
    struct stockTV
    {
        double price;
    	int stockID;
    };
    
    const int MAXTV = 7;
    
    int main()
    {
    	stockTV data[MAXTV] = { 
            { 455.0, 1080 }, 
            { 1195.0, 2570 }, 
            { 650, 4188 }, 
            { 262, 4215 }, 
            { 799, 6696 }, 
            { 490, 3650 }, 
            { 525.0, 3923 } 
        };
    
    	auto lowest = std::min_element(std::begin(data), std::end(data),
    		[](const stockTV& a, const stockTV& b) { 
                return a.price < b.price; 
            }
        );
    
    	std::cout << "Cheapest TV: " << lowest->stockID << ", price: " << lowest->price;
    }
