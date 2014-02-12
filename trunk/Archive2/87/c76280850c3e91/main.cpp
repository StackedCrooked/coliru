#include <vector>
#include <iostream>

class B
{
public:
    B() : x(0) {}
    B(const B &r) : x(r.x) { std::cout << "Copied" << std::endl; }
    B(B&& r) : x(r.x) { std::cout << "Moved" << std::endl; r.x = 0; }
    B& operator =(B r) { x = std::move(r.x); return *this; }

    explicit B(int x) : x(x) {}
    int get() const { return x; }
    
private:
    int x;
};

class C
{
public:
    template<typename ...T>
    C(T&& ...x)
    {
        add(std::forward<T>(x)...);
    }
    
    template<typename T>
    C(std::vector<T>& x)
    {
        std::cout << "Vector! " << x.size() << std::endl;
    }
    
    template<typename T>
    C(std::vector<T>&& x)
    {
        std::cout << "RValue Vector! " << x.size() << std::endl;
    }
    
    void add() {}
    
    template<typename T>
    void add(T r) { std::cout << r.get() << std::endl; }
    
    template<typename T, typename ...Rest>
    void add(T&& r, Rest ...s) {
        std::cout << r.get() << std::endl;
        add(std::forward<Rest>(s)...);
    }
};

int main()
{
    std::vector<int> v;
    std::vector<int> const cv;
    
    C a(B(1), B(2), B(3));
    C b(v);
    C c(std::vector<int>(10));
    C d(cv);
}
