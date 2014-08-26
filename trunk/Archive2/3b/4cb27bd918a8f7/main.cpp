#include <iostream>

class First;
class Second;

class First
{
public:
    First()             = default;
    First(const First&) = default;
    explicit First(const Second&); 
    int value() const { return x; }    
protected:
    ~First() = default;
private:
    int x = 1;
};

class Second
{
public:
    Second()              = default;
    Second(const Second&) = default;
    explicit Second(const First&);
    int value() const { return x; }
protected:
    ~Second() = default;
private:
    int x = 2;
};

First::First(const Second& s): x(s.value()) {}
Second::Second(const First& f): x(f.value()) {}

template<class Policy>
class Host
: 
    public Policy
{
public:    
    Host() = default;
    
    template<class U>
    Host(Host<U> const& other)
    :
        Policy(other)
    {}
};

int main()
{
    Host<First> h1;
    Host<Second> h2;
    Host<Second> h3(h1);
    Host<First> h4(h2);
    
    std::cout << h1.value() << "\n";
    std::cout << h2.value() << "\n";
    std::cout << h3.value() << "\n";
    std::cout << h4.value() << "\n";
}