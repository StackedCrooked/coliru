#include <utility>


int main()
{
    struct TestPair
    {
        operator std::pair<int, int>() const  { return pair; }
        std::pair<int, int> pair;
    };
    
    
    struct Test
    {
        Test() : n() {}
        operator int() const { return n; }
        int n;
    };
    
    
    Test() < Test(); // operator< found through operator int
        
    
    TestPair() < TestPair(); // error
}
