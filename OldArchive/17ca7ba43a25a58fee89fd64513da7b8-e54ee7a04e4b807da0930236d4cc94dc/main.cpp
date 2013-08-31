#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}

template <class T, class U>
auto do_stuff(const T& t, const U& u) -> decltype(t+u) { return t + u; }

struct the_struct
{
    int     x;
    double  y;
    std::string s;
};
the_struct s = { 3, 3.14, "pi" };

class A
{
    public:
    
    A() : _x(1), _y(2) { std::cout << "A::A()" << std::endl; }
    A(int x, int y) : _x(x), _y(y) { std::cout << "A::A(int,int)" << std::endl; }
    virtual ~A() { }
    
    virtual void proc() { std::cout << "A::proc" << std::endl; }
    virtual void finalProc() final { std::cout << "A::finalProc" << std::endl; } 
    
    friend std::ostream& operator<<(std::ostream& os, const A& a);
    
    protected:
    
    int _x, _y;
};

constexpr int one_eight_seven() { return 187; }

class B : public A
{
    public:
    
    using A::A;
    
    // N.B.: default constructors are NOT inherited by "using A::A"
    B() = default;
    B(int x, int y, int z) : B(x,y) { std::cout << "B::B(int,int,int)" << std::endl; }
    B(const B&) = delete;
    
    virtual void proc() override { std::cout << "B::proc" << std::endl; }
    //virtual void proc2() override { std::cout << "Error: not actually overriding anything." << std::endl; }
    //virtual void finalProc() { std::cout << "Error: cannot override a final function." << std::endl; }
    
    friend std::ostream& operator<<(std::ostream& os, const B& b);
    
    protected:
    
    int _z = one_eight_seven();
};

std::ostream& operator<<(std::ostream& os, const A& a) { return (os << "A{" << a._x << "," << a._y << "}"); }
std::ostream& operator<<(std::ostream& os, const B& b) { return (os << "B{" << b._x << "," << b._y << "," << b._z << "}"); }

template <typename T, typename U>
class SequenceMultiplier
{
    public:
    
    SequenceMultiplier() = delete;
    SequenceMultiplier(const SequenceMultiplier&) = delete;
    SequenceMultiplier(SequenceMultiplier&& rht)
    {
        std::cout << "SequenceMultiplier::SequenceMultiplier(SequenceMultiplier&&)" << std::endl;
        std::cout << "this._v: " << std::hex << &_v[0] << " rht._v: " << &rht._v[0] << std::endl;
        //std::move(rht._v.begin(), rht._v.end(), _v.begin());
        _v = std::move(rht._v);
        std::cout << "this._v: " << std::hex << &_v[0] << " rht._v: " << &rht._v[0] << std::endl;
    }
    
    SequenceMultiplier(const std::initializer_list<T>& l, const U& u) : _v(l), _m(u) 
    {
        static_assert(std::is_arithmetic<T>::value && std::is_arithmetic<U>::value, "Types T and U must be numeric.");
        std::cout << "SequenceMultiplier::SequenceMultiplier() got: ";
        for(auto t : l) std::cout << " " << t << " ";
        std::cout << std::endl;
    }
    
    void multiply() 
    { 
        std::cout << "SequenceMultiplier::multiply(): ";
        // Note that the type of t is int, not vector<int>::iterator
        //for(auto t : _v) t *= _m;
        for(T& t : _v) t *= _m;
        std::cout << *this << std::endl;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const SequenceMultiplier& sm)
    {
        std::cout << "SequenceMultiplier{";
        for(auto t : sm._v)
            os << " " << t < " ";
        os << "}";
        return os;
    }
    
    private:
    
    std::vector<T> _v;
    U _m;
};

template <typename U>
using IntegerSequenceMultiplier = SequenceMultiplier<int,U>;

enum class Constants
{
    One = 1,
    Two,
    Three,
};

//Constants c1 = One; Error: 'enum class' will not inject values into the enclosing namespace
Constants c2 = Constants::Two;

enum class Constants2 : long long
{
    One = 1,
    Two, 
    Three,
};

enum Constants3 : int
{
    Four = 4,
};

int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
    
    std::vector<int> v = { 0, 1, 2, 3, 318 };
    for(int& i : v)
        std::cout << " " << i << " ";
    std::cout << std::endl;
    
    std::for_each(v.begin(), v.end(), [] (int i) { std::cout << "lambda: " << i << std::endl; });
    
    for(auto iter=v.begin(); iter != v.end(); iter++)
        std::cout << "auto: " << *iter << std::endl;
    std::cout << std::endl;
    
    int x = 5;
    float y = 2.78;
    std::cout << "do_stuff(" << x << ", " << y << ") = " << do_stuff(x, y) << std::endl;  
    
    A a;
    std::cout << a << std::endl;
    a.proc();
    a.finalProc();
    
    B b1;
    std::cout << b1 << std::endl;
    b1.proc();
    
    B b2(11,12,13);
    std::cout << b2 << std::endl;
    
    B b3{14,15,16};
    std::cout << b3 << std::endl;
    
    B b4 = { 17,18,19 };
    std::cout << b4 << std::endl;
    
    // B::B(const B&) is deleted
    //B b5 = b4;
    
    std::cout << std::endl;
    IntegerSequenceMultiplier<float> sm = { { 1, 1, 2, 3, 5, 8, 13 }, 1.5f };
    sm.multiply();
    //IntegerSequenceMultiplier<float> sm2({1,2}, 100f);
    IntegerSequenceMultiplier<float> sm2(std::move(sm)); //{ {100,200}, 3.0 };
    std::cout << "sm: " << sm << std::endl << "sm2: " << sm2 << std::endl;
    //sm2 = sm;
    
    std::cout << std::endl;
    std::cout << "sizeof(Constants::One)=" << sizeof(Constants::One) << " sizeof(Constants2::One)=" << sizeof(Constants2::One) << std::endl;
    Constants3 c4 = Four;
    
    std::cout << std::endl << "Have a nice day." << std::endl;
}
