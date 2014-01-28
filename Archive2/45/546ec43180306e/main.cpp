#include <memory>
#include <typeindex>
#include <utility>
#include <iostream>
#include <vector>
#include <map>

class my_collection
{
private:
    struct base
    {
        virtual void print() const = 0;
    };
    
    template<class T>
    struct wrapper : base
    {
        std::vector<T> m;
        
        virtual void print() const final override
        {
            std::cout << typeid(T).name() << ": ";
            for(auto const& e : m) std::cout << e << ", ";
        }
    };
    
    std::map<std::type_index, std::unique_ptr<base>> coll;

public:
    template<class T, class... Args>
    void emplace_back(Args&&... args)
    {
        std::type_index t {typeid(T)};
        auto& f = coll[t];
        if(!f) f.reset(new wrapper<T>);
        wrapper<T>* cf = static_cast<wrapper<T>*>(f.get());
        cf->m.emplace_back(std::forward<Args>(args)...);
    }
    
    void print_all()
    {
        for(auto const& e : coll)
        { e.second->print(); std::cout << "\n"; }
    }
};

struct foo
{
    int m;
    foo(int p) : m(p) {}
};

std::ostream& operator<<(std::ostream& o, foo const& f)
{
    return o << "[" << f.m << "]";
}

int main()
{
    my_collection m;
    m.emplace_back<int>(42);
    m.emplace_back<int>(1);
    m.emplace_back<int>(3);
    m.emplace_back<double>(1.2);
    m.emplace_back<double>(2.3);
    m.emplace_back<double>(3.4);
    m.emplace_back<foo>(1114);
    m.emplace_back<foo>(1115);
    m.print_all();
}