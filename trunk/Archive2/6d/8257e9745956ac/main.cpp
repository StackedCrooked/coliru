#include <iostream>
#include <functional>
#include <queue>
#include <future>
#include <type_traits>
#include <algorithm>

class A
{
    public:
        A() = default;
        ~A() = default;
};

class TMP
{
    public:
        TMP() = default;
        ~TMP() = default;
        
        void add(const A& a)
        {
            vec.push_back(&a);
        }
        
        void erase(const A& a)
        {
            auto it = find(a);
            
            if (it != vec.end())
                vec.erase(it);
        }
        
        std::vector<const A*>::const_iterator find(const A& a) const
        {
            return std::find(vec.begin(), vec.end(), &a);
        }
    
    private:
        std::vector<const A*> vec;
};

int main()
{
    TMP tmp;
    
    A a1;
    
    tmp.add(a1);
    tmp.erase(a1);
    
    return 0;
}