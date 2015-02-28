#include <string>
#include <array>

template<int N>
struct Item : Item<N - 1>
{
    Item()
    {
        ara[0].resize(N);
    }
    
    #if A == 1
    
        ~Item() = default;
    
    #elif A == 2
    
        ~Item() {}
    
    #else
    
        virtual ~Item() {}
    
    #endif
    
    
    std::array<std::string, N> ara;

};

template<>
struct Item<0>
{
};



template<typename T> T get();
template<typename T> void set(T);


void test()
{
    set(get<Item<4>>());
}
