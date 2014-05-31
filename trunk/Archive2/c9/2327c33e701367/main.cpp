#include <functional>
#include <iostream>
#include <string>
#include <memory>

using namespace std;

template<typename T>
class Property
{
public:
    Property(const T&& value) : m_value(new T(value), default_delete<T>()) { cout << "const rvalue reference ctor" << endl; }
    Property(const T& value) : m_value(new T(value), default_delete<T>()) { cout << "const lvalue ctor" << endl; }
    Property(T& value) : m_value(&value, [](T* value) {}) { cout << "lvalue ctor" << endl; }
    Property(T* value) : m_value(value, default_delete<T>()) { cout << "pointer ctor" << endl; }
    
    const T& operator()() const { return *m_value; }
    
    Property<T>& operator=(const T& value)
    {
        *m_value = value;
        return *this;
    }
    
private:
    unique_ptr<T, function<void(T*)>> m_value;
};

void foo(const string& x)
{
    Property<string> p(x);
    p = "5";
    
    cout << "x = " << x << endl;
    cout << "p = " << p() << endl;
}

int main()
{
    string x = "0";
    
    foo(x);
    
    Property<string> p("0");
    p = "5";
    
    cout << "x = " << x << endl;
    cout << "p = " << p() << endl;
    
    return 0;
}
