#include <functional>
#include <vector>
#include <iostream>

template <typename...Params>
class Delegate {
private:

    typedef std::function < void(Params...)> FunctionType;
    struct Key {
        void*         m_object;
        size_t        m_funcHash;
        FunctionType  m_func;

        Key(void* object, size_t funcHash, FunctionType func) : m_object(object), m_funcHash(funcHash), m_func(func)
        {}

        bool operator==(const Key& other) const {
            return other.m_object == m_object && other.m_funcHash == m_funcHash;
        }
    };

    std::vector <Key> m_functions;

public:
    template <typename Class>
    void connect(Class& obj, void (Class::*func)(Params...)) {
        std::function < void (Class, Params...) >  f = [func](Class c, Params... params) { std::cout << "passthrough on a copy! " << &c << "\n"; return (c.*func)(params...); };
        FunctionType fun = [&obj, f](Params... params) {
            f(obj, params...);
        };
        size_t hash = getHash(func);
        m_functions.push_back(Key(&obj, hash, fun));
    }

    template <typename Class>
    size_t getHash(void (Class::*func)(Params...)) {
        const char *ptrptr = static_cast<const char*>(static_cast<const void*>(&func));
        int size = sizeof(func);
        std::string str_rep(ptrptr, size);
        std::hash<std::string> strHasher;
        return strHasher(str_rep);
    }

    template <typename Class>
    void disconnect(Class& obj, void (Class::*func)(Params...)) {
        size_t hash = getHash(func);
        for(unsigned int i = 0; i < m_functions.size(); ++i) {
            auto key = m_functions[i];
            if(key.m_funcHash == hash && key.m_object == &obj) {
                m_functions.erase(m_functions.begin() + i);
                --i;
            }
        }
    }

    template <typename ... Args>
    void operator()(Args...args) {
for(auto & key : m_functions) {
            key.m_func(args...);
        }
    }
};


class BaseClass {

public:
    virtual void print(const std::string& str) = 0;
};

class A : public BaseClass {
public:
    void print(const std::string& str) {
        std::cout << " Class A : Print [" << str << "]\n";
    }

};

class B : public BaseClass {
public:
    void print(const std::string& str) {
        std::cout << " Class B : Print [" << str << "]\n";
    }
};

int main() {
    A a;
    B b;
    std::cout << "A instance a is at " << &a << "\n";
    std::cout << "B instance b is at " << &b << "\n";
    Delegate <const std::string&> delegate;
    delegate.connect(a, &A::print);
    delegate.connect(b, &B::print);
    delegate("hello");
    delegate("world");
    delegate.disconnect(a, &A::print);
    delegate("bye world");
    delegate.disconnect(b, &B::print);
    delegate("nobody there.");  // should not print anything
}
