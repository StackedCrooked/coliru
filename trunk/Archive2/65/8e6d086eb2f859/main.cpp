#include <functional>
#include <iostream>
#include <map>
#include <tuple>

template <typename... Params>
class Delegate {
private:
    typedef std::function<void(Params...)> FunctionType;

    struct Key {
        void*  m_object;
        size_t m_funcHash;

        bool operator==(const Key& other) const { return tuple() == other.tuple(); }
        bool operator< (const Key& other) const { return tuple() <  other.tuple(); }
      private:
        std::tuple<void* const&, size_t const&> tuple() const { return std::tie(m_object, m_funcHash); }
    };

    std::multimap<Key, FunctionType> m_functions;

public:
    bool empty() const { return m_functions.empty(); }
    void clear() { m_functions.clear(); }

    template <typename Class>
    void connect(Class& obj, void (Class::*func)(Params...)) {
        m_functions.insert({
                Key {&obj, getHash(func)}, 
                [&obj, func](Params... params) {
                    (obj.*func)(params...);
                }
            });
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
        m_functions.erase(Key { &obj, getHash(func) });
    }

    template <typename ... Args>
    void operator()(Args...args) {
        for(auto const& key : m_functions) key.second(args...);
    }
};

//////////////////////////////////
// demonstration
struct BaseClass {
    virtual void print(const std::string& str) = 0;
};

struct A : BaseClass {
    void print(const std::string& str) { std::cout << " Class A : Print [" << str << "]\n"; }
};

struct B : BaseClass {
    void print(const std::string& str) { std::cout << " Class B : Print [" << str << "]\n"; }
};

#include <cassert>

int main() {
    Delegate <const std::string&> delegate;
    A a;
    for (int i = 0; i < 5; ++i)
        delegate.connect(a, &A::print);

    delegate("check");

    delegate.disconnect(a, &A::print);

    delegate("nobody there.");  // does not print anything

    assert(delegate.empty());
    delegate.disconnect(a, &A::print); // no effect
}
