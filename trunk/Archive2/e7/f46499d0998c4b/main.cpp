#include <functional>
#include <iostream>
#include <map>
#include <tuple>
#include <cstdint>
#include <cstring>
#include <typeindex>

template <typename... Params>
class Delegate {
private:
    typedef std::function<void(Params...)> FunctionType;

    struct Key {
        void const*  m_object;
        uintmax_t m_funcHash;

        bool operator==(const Key& other) const { return tuple() == other.tuple(); }
        bool operator< (const Key& other) const { return tuple() <  other.tuple(); }
      private:
        std::tuple<void const* const&, uintmax_t const&> tuple() const { return std::tie(m_object, m_funcHash); }
    };

    std::multimap<Key, FunctionType> m_functions;

public:
    bool empty() const { return m_functions.empty(); }
    void clear() { m_functions.clear(); }

    template <typename Class, typename Class2>
    void connect(Class& obj, void (Class2::*func)(Params...) const) {
        m_functions.insert({
                Key {&obj, getHash(func)}, 
                [&obj, func](Params... params) {
                    (obj.*func)(params...);
                }
            });
    }

    template <typename Class>
    uintmax_t getHash(void (Class::*func)(Params...) const) {
        const char *ptrptr = static_cast<const char*>(static_cast<const void*>(&func));
        uintmax_t id = 0;
        memcpy(&id, ptrptr, sizeof(func));
        return id;
    }

    template <typename Class, typename Class2>
    void disconnect(Class& obj, void (Class2::*func)(Params...) const) {
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
    virtual void print(const std::string& str) const = 0;
};

struct A : BaseClass {
    A(){}
    void print(const std::string& str) const { std::cout << " Class A : Print [" << str << "]\n"; }
};

struct B : BaseClass {
    B(){}
    void print(const std::string& str) const {}
};

#include <cassert>

int main() {
    Delegate <const std::string&> delegate;

    A a;
    for (int i = 0; i < 5; ++i)
        delegate.connect(a, &A::print);

    delegate("check");

    delegate.disconnect(a, &B::print);

    delegate("nobody there.");  // Oops... not printed
    assert(!delegate.empty());
}
