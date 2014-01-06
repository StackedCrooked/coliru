    #include <iostream>
    #include <random>
    #include <cstdlib>
    
    int main()
    {
        std::random_device rd;
    
        std::mt19937 e2(rd());
    
        int V = 10 ;
    
        std::uniform_int_distribution<int> dist1(0, V);
    
    
        for (int i = 0; i < V; ++i)
        {
            for (int k = i+1; k < V; ++k)
            {
                int index1 = dist1(e2) ;
                int index2 = dist1(e2) ;
                std::cout << "( " <<  index1 << " , " << index2 << ") " ;
            }
            std::cout << std::endl ;
        }
        std::cout << std::endl ;
    }
