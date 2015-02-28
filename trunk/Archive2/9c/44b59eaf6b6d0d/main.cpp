

template<int N>
struct Item : Item<N - 1>
{
    
    #if A == 1
    
        ~Item() = default;
    
    #elif A == 2
    
        ~Item() {}
    
    #else
    
        virtual ~Item() {}
    
    #endif

};

template<>
struct Item<0>
{
};


Item<4> item;
