#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <functional>
#include <typeinfo>

// -------------------------------------------------------------------------------------------
// Script types
// -------------------------------------------------------------------------------------------

// Fast coded, here for the example (so you should not mind the void*)
class Variable
{
    void* v;
    size_t type_hash;

public:
    Variable() : v(nullptr), type_hash(0) {}
    template<typename T> Variable(const T& var) : v((void*)&var), type_hash(typeid(T).hash_code()) {}

    template<typename T>
    T* getExternObject() const
    {
        if(typeid(T).hash_code() != type_hash)
            std::cout << "(bad conversion)";
        return (T*)v; // For test
    }
};

// -------------------------------------------------------------------------------------------
// Templates for automatic wrap
// -------------------------------------------------------------------------------------------

/// Predicate, do we need to convert 'T' to 'Variable' ?
template<typename T>
struct need_wrap
{
    static const bool is_simple =
        std::is_integral<T>::value
        || std::is_floating_point<T>::value
        || std::is_same<T, bool>::value;
    static const bool value = !is_simple;
};

/// Wrap 'T' in 'Variable' if needed (the struct is needed for vs)
template<typename T>
struct wrap_helper
{
    typedef typename std::conditional<need_wrap<T>::value, Variable, T>::type type;
};

template<typename T>
using wrap = typename wrap_helper<T>::type;

/// Unwrap, from 'Variable' to 'T' (if it was wrapped)
template<typename T, bool = need_wrap<T>::value>
struct unwrap
{
    static const T& get(const wrap<T>& var)
    {
        return *var.template getExternObject<typename std::remove_reference<T>::type>();
    }
};

template<typename T>
struct unwrap<T,false>
{
    static T get(const wrap<T>& var)
    {
        return var;
    }
};

/// Base class of objects that can be scripted
struct Scriptable
{
    /// The wrapped function that will be exported
    template<typename F, typename R, typename... Arg>
    R wrapped(wrap<Arg>... args)
    {
        return F::call((typename F::class_type*)this, unwrap<Arg>::get(args)...);
    }

    /// Compile-time representation of a pointer to member function
    template<typename C, typename R, typename... Arg>
    struct member_func_ptr
    {
        /// Genericly store a pointer to member function
        template<R (C::* func)(Arg...)>
        struct store
        {
            /// Type of the class to which the function belongs
            typedef C class_type;

            /// Call the stored function
            static R call(C* obj, Arg... args)
            {
                return (obj->*func)(args...);
            }
        };

        /// Type of the wrapped function around the specified member
        typedef R (C::* wrapped_type)(wrap<Arg>...);

        /// Instantiate the wrapper function and return it
        template<R (C::* func) (Arg...)>
        static wrapped_type to_script()
        {
            return &C::template wrapped<store<func>, R, Arg...>;
        }
    };

    /// Return the pointer to member representation (avoid explicitely typing the type by using argument deduction)
    template<typename C, typename R, typename... Arg>
    static member_func_ptr<C, R, Arg...> member_ptr(R (C::*) (Arg...))
    {
        return member_func_ptr<C, R, Arg...>();
    }
};

// -------------------------------------------------------------------------------------------
// Use case
// -------------------------------------------------------------------------------------------

struct Interpreter // or whatever
{
    std::function<int (const Variable&, int, const Variable&)> my_func;
    std::function<void (const Variable&, const Variable&)> my_other_func;
    std::function<float (bool)> enable_stuff;
    std::function<void ()> no_params;
};

class A { public: int v; };
struct B { bool v; };
class C { public: float v; };

class Test : public Scriptable
{
public:
    int myfunc(const A& a, int b, C c)
    {
        int res = (int)(b + a.v + c.v);
        std::cout << std::boolalpha << "Test::myfunc(A { " << a.v << " }, " << b << ", C { " << c.v << " }) = " << res << "\n";
        return res;
    }

    void myotherfunc(const B& a, const A& b)
    {
        std::cout << std::boolalpha << "Test::myotherfunc(B { " << a.v << " }, A { " << b.v << " })\n";
    }

    float enablestuff(bool e)
    {
        float res = e ? 3.14159 : 2.71828;
        std::cout << std::boolalpha << "Test::enablestuff(" << e << ") = " << res << "\n";
        return res;
    }

    void noparams()
    {
        std::cout << "Test::noparams()\n";
    }

    void export_functions(Interpreter& i)
    {
        using namespace std::placeholders;
        i.my_func       = std::bind(member_ptr(&Test::myfunc).to_script<&Test::myfunc>(),           this, _1, _2, _3);
        i.my_other_func = std::bind(member_ptr(&Test::myotherfunc).to_script<&Test::myotherfunc>(), this, _1, _2);
        i.enable_stuff  = std::bind(member_ptr(&Test::enablestuff).to_script<&Test::enablestuff>(), this, _1);
        i.no_params     = std::bind(member_ptr(&Test::noparams).to_script<&Test::noparams>(),       this);
    }
};

int main()
{
    Test t;
    Interpreter i;

    t.export_functions(i);

    A a = { 42 };
    B b = { true };
    C c = { 123.456f };

    Variable va(a);
    Variable vb(b);
    Variable vc(c);

    int u = i.my_func(va, 2, vc);
    std::cout << "  Returned value: " << u << "\n";
    i.my_other_func(vb, va);
    float v = i.enable_stuff(false);
    std::cout << "  Returned value: " << v << "\n";
    i.no_params();
}













