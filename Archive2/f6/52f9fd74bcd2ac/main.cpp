#include <iostream>

template <class T>
T add(T a, T b)
{
    return a+b;
}

template <class T>
T mult(T a, T b)
{
    return a*b;
}

template<class T>
class A
{
public:
    explicit A(const T& a): _a(a),
                            _id(getId())
    {
        std::cout<<"A created with id "<< GetId()
                 <<" and value " <<GetA() << std::endl;
    }

    A(const A& rhs): _a( rhs.GetA()),
                    _id( rhs._id)
    {}

    ~A() {}

    const T GetA() const {return _a;}
    const unsigned short GetId() const {return _id;}

    A& operator+=(const A& rhs)
    {
        _a+=rhs.GetA();
        return *this;
    }

    A& operator+(const A& rhs)
    {
        _a += rhs.GetA();
        return *this;
    }

    A& operator*(const A& rhs)
    {
        _a *= rhs.GetA();
        return *this;
    }

    A& operator=(const A& rhs)
    {
        _a = rhs.GetA();
        return *this;
    }

    bool operator==(const A& rhs) const
    {
        return _a == rhs.GetA() ? true : false;
    }

private:
    A(){};

    static unsigned short idx;

    unsigned short getId() { return idx++;}

    T _a;
    const unsigned short _id;

    template<class U>
        friend std::ostream& operator<<(std::ostream& os, const A<U>& a);
};

template<class T>
    std::ostream& operator<<(std::ostream& os, const A<T>& a)
{
    os << "Overloaded " << a.GetA() << " id: " << a.GetId() << std::endl;
    return os;
}

template<class T> unsigned short A<T>::idx = 0;

int main()
{
    A<int> a(1), b(2), c(3), d(0);

    c = add( a, b );
    d = mult( c,a );

    std::cout<<a<<b<<c<<d<<std::endl;

    return 0;
}