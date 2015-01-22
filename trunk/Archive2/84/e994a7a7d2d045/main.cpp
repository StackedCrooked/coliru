#include <iostream>
#include <memory>

class Base
{
public:
    virtual ~Base() = default;
    virtual bool acceptsData(const char*) = 0;
    virtual void print() const = 0;
};

class Derived1 : public Base
{
public:
    bool acceptsData(const char* s) override { return std::string(s) == "D1"; }
    void print() const override { std::cout << "Derived1\n"; }
};

class Derived2 : public Base
{
public:
    bool acceptsData(const char* s) override { return std::string(s) == "D2"; }
    void print() const override { std::cout << "Derived2\n"; }
};

namespace detail
{
    template <typename T> std::unique_ptr<Base> make_base(const char* data)
    {
        std::unique_ptr<Base> base = std::make_unique<T>();
        if(base->acceptsData(data)) {
            return base;
        }
        return nullptr;
    }
    
    template <typename... Ts> std::unique_ptr<Base> createStuff(const char* data)
    {
        std::function<std::unique_ptr<Base>(const char*)> fs[] = { make_base<Ts>... };
    
        for(auto& f : fs) {
            auto base = f(data);
            if(base) {
                return base;
            }
        }
        return nullptr;
    }
}

std::unique_ptr<Base> createStuff(const char* data) { return detail::createStuff<Derived1, Derived2>(data); }

int main()
{
    std::unique_ptr<Base> Aclass = createStuff("D1");

    if(Aclass) {
        Aclass->print();
    }
    Aclass = createStuff("D2");
    if(Aclass) {
        Aclass->print();
    }
}
