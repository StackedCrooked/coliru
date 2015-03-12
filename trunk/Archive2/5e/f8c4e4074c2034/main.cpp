#include <iostream>

template<unsigned int Size>
struct asdf {
    asdf(int (&things)[Size]) {
        
        for(int i = 0; i < Size; i++) {
            this->things[i] = things[i];
        }
        std::cout << this->things[0] << std::endl;
    }

    
    private:
        int things[Size] = {};
};

int main()
{
    int myThings[] = { 4, 5, 6 };
    auto a = asdf<3>(myThings);
   
    return 1;
}