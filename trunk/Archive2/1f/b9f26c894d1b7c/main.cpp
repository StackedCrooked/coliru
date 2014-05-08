    #include <stdio.h>
    #include <time.h>
    #include <mutex>
    #include <iostream>
    #include <vector>
    #include <bitset>

template<typename U>
class arrayInitializer
{
    U m_array;
    public:
        template<typename ...T>
        arrayInitializer(T&&...t):m_array{ std::forward<T>(t)... } 
        {
        
        }
        
        operator U(){
        return m_array;
        }
};

        

int main(){
    
  std::vector<int> arrayTest = arrayInitializer<std::vector<int>>{1,2,3,4,5,6};

    for(int i : arrayTest){
        std::cout << i << std::endl;
    }
 
}