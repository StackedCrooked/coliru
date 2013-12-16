#include <functional>
#include <iostream>
#include <map>
#include <tuple>
#include <cstdint>
#include <cstring>
#include <array>
#include <typeindex>

template <typename... Params>
class Delegate {
private:
    ////////////////////////////////////////////////////////////////////
    // Traits to Sfinae on pointer-to-void-member-function (so we don't need to
    // cv-qualify all overloads)
    template <typename PtrToMemFun> struct is_ptvmf : std::false_type { };
    template <class Class, typename... Args> struct is_ptvmf<void (Class::*)(Args...)> : std::true_type {};
    template <class Class, typename... Args> struct is_ptvmf<void (Class::*)(Args...) const> : std::true_type {};
    template <class Class, typename... Args> struct is_ptvmf<void (Class::*)(Args...) volatile> : std::true_type {};
    template <class Class, typename... Args> struct is_ptvmf<void (Class::*)(Args...) const volatile> : std::true_type {};
    ////////////////////////////////////////////////////////////////////

    typedef std::function<void(Params...)> FunctionType;
    typedef std::array<uintmax_t, 2> PtmfRepresentation;

    struct Key {
        void const volatile* m_object;
        std::type_index m_type;
        PtmfRepresentation m_ptmf_representation;

        bool operator==(const Key& other) const { return tuple() == other.tuple(); }
        bool operator< (const Key& other) const { return tuple() <  other.tuple(); }
      private:
        std::tuple<void const volatile* const&, std::type_index const&, PtmfRepresentation const&> tuple() const { return std::tie(m_object, m_type, m_ptmf_representation); }
    };

    std::multimap<Key, FunctionType> m_functions;

    template <typename PtrToMemFun>
    PtmfRepresentation getHash(PtrToMemFun func) {
        const char *ptrptr = static_cast<const char*>(static_cast<const void*>(&func));
        PtmfRepresentation id {{0}};
        static_assert(sizeof(func) <= sizeof(id), "ptmf representation too large");
        memcpy(&id, ptrptr, sizeof(func));
        return id;
    }

public:
    bool empty() const { return m_functions.empty(); }
    void clear() { m_functions.clear(); }

    template <typename Class, typename PtrToMemFun, typename Sfinae = typename std::enable_if<is_ptvmf<PtrToMemFun>::value, void>::type >
    void connect(Class& obj, PtrToMemFun func) {
        m_functions.insert({
                Key {&obj, typeid(func), getHash(func)}, 
                [&obj, func](Params... params) {
                    (obj.*func)(params...);
                }
            });
    }

    template <typename Class, typename PtrToMemFun, typename Sfinae = typename std::enable_if<is_ptvmf<PtrToMemFun>::value, void>::type >
    void disconnect(Class& obj, PtrToMemFun func) {
        m_functions.erase(Key { &obj, typeid(func), getHash(func) });
    }

    template <typename ... Args>
    void operator()(Args...args) {
        for(auto const& key : m_functions) key.second(args...);
    }
};

//////////////////////////////////
// demonstration
#define CV_QUALIFIER const volatile
struct BaseClass {
    virtual void print(const std::string& str) CV_QUALIFIER = 0;
};

struct A : BaseClass {
    A(){}
    void print(const std::string& str) CV_QUALIFIER { std::cout << " Class A : Print [" << str << "]\n"; }
};

struct B : BaseClass {
    B(){}
    void print(const std::string& str) CV_QUALIFIER { std::cout << " Class B : Print [" << str << "]\n"; }
};

#include <cassert>

int main() {
    Delegate <const std::string&> delegate;

    A CV_QUALIFIER a;
    for (int i = 0; i < 5; ++i)
        delegate.connect(a, &A::print);

    B CV_QUALIFIER b;
    delegate.connect(b, &B::print);

    delegate("check");

    delegate.disconnect(b, &B::print);
    delegate.disconnect(a, &B::print);

    delegate("still there.");
    assert(!delegate.empty());

    delegate.disconnect(a, &A::print);

    delegate("nobody there."); 
    assert(delegate.empty());
}
