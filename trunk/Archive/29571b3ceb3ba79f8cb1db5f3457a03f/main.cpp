#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <typeinfo>


struct LeakChecker
{   
    static LeakChecker& Get()
    {
        static LeakChecker fLeakChecker;
        return fLeakChecker;
    }
    
    ~LeakChecker()
    {
        if (!mObj.empty())
        {
            std::cerr << std::endl << "*** Leaks detected ***" << std::endl;
            std::cerr << mObj.size() << " objects leaked: " << std::endl;
            for (auto s : mObj)
            {
                std::cerr << "Name: " << s << "." << std::endl;
            }       
        }
    }
    
    template<typename T>
    void insert(T *)
    {
        auto name = typeid(T).name();
        std::cerr << "insert: " << name << std::endl; 
        mObj.insert(name);
    }
    
    template<typename T>
    void erase(T *)
    {
        auto name = typeid(T).name();
        std::cerr << "erase: " << name << std::endl;
        mObj.erase(name);
    }
    
private:
    LeakChecker() {}
    std::set<std::string> mObj;
};

template<typename T>
struct Checked
{
    Checked()
    {
        LeakChecker::Get().insert(static_cast<T*>(this));
    }
    
    ~Checked()
    {
        LeakChecker::Get().erase(static_cast<T*>(this));
    }
};

struct Item : Checked<Item>
{
};

int main()
{
    new Item();
}