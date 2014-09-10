#include <map>
#include <unordered_map>

template <typename MAP>
void generic_foo(MAP& map)
{
    
}

template <class Key,                                    
          class T,                                   
          class Hash,                       
          class Pred,                  
          class Alloc>
void foo(std::unordered_map<Key, T, Hash, Pred, Alloc>& m)
{
    generic_foo(m);
}
        
template <class Key,                                    
          class T,                          
          class Compare,                  
          class Alloc>
void foo(std::map<Key, T, Compare, Alloc>& m)
{
    generic_foo(m);
}        

// Tests:

struct MyHash
{
    size_t operator()(int x) const { return x; }
};

int main()
{
    std::unordered_map<float, int> m1;
    std::unordered_map<int, int, MyHash> m2;
    std::map<int, int, std::less<int>> m3;
    std::map<int, int, std::greater<int>> m4;
    
    foo(m1);
    foo(m2);
    foo(m3);
    foo(m4);   
}
