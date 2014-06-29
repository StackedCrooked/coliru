#include <functional>
#include <memory>
#include <iostream>
#include <type_traits>

////    New Callback template
template<class>
class Callback; /* undefined */

template<class R, class... Args>
class Callback<R(Args...)> {
public:
    typedef std::function<R(Args...)>       FunctionType;
    typedef std::shared_ptr<FunctionType>   FunctionPointer;

    //! \group Callback Constructors
    //! \{

    //! Empty Callback constructor.
    Callback()
        : func() { }

    //! Callback copy constructor.
    Callback(const Callback & other)
        : func(other.func) { }

    //! Callback move constructor.
    Callback(Callback && other)
        : func(other.func) { }

    Callback(const FunctionType &function)
        : func(std::make_shared<FunctionType>(function)) { }

    static Callback from_function(const FunctionType &function) {
        return Callback(function);
    }

    template<class UserData, R(*Function)(Args..., UserData)>
    static Callback from_function_e(UserData userdata) {
        return Callback(
            [=](Args && ... args) -> R {
                return function_caller_e<UserData, Function>(std::forward<Args>(args)..., userdata);
            }
        );
    }

    template<class C, R(C::*CMethod)(Args...)>
    static Callback from_method(C * instance) {
        return Callback(
            [=](Args && ... args) -> R {
                return method_caller<C, CMethod>(instance, std::forward<Args>(args)...);
            }
        );
    }

    template<class C, class UserData, R(C::*CMethod)(Args..., UserData)>
    static Callback from_method_e(C * instance, UserData userdata) {
        return Callback(
            [=](Args && ... args) -> R {
                return method_caller_e<C, UserData, CMethod>(instance, std::forward<Args>(args)..., userdata);
            }
        );
    }

    //! \}

    //! \group Callback function comparators
    //! \{
    bool operator==(const Callback<R(Args...)> &other) const
    {
        return   func == other.func;
    }

    bool operator!=(const Callback<R(Args...)> &other) const
    {
        return !(func == other.func);
    }
    //! \}

    //! \group Callback function setters
    //! \{
    Callback & operator=(const Callback<R(Args...)> &other)
    {
        if (this != &other)
        {
            func = other.func;
        }
        return *this;
    }

    Callback & operator=(Callback<R(Args...)> &&other)
    {
        func = std::move(other.func);
        return *this;
    }

    Callback & set(const FunctionType &function)
    {
        func = std::make_shared<FunctionType>(function);
        return *this;
    }

    template<class UserData, R(*Function)(Args..., UserData)>
    Callback & set(UserData userdata)
    {
        func = from_function_e<UserData, Function>(userdata).func;
        return *this;
    }

    template<class C, R(C::*CMethod)(Args...)>
    Callback & set(C * instance)
    {
        func = from_method<C, CMethod>(instance).func;
        return *this;
    }

    template<class C, class UserData, R(C::*CMethod)(Args..., UserData)>
    Callback & set(C * instance, UserData userdata)
    {
        func = from_method_e<C, UserData, CMethod>(instance, userdata).func;
        return *this;
    }
    //! \}

    //! Invoke the callback with the supplied arguments.
    R invoke_move(Args && ... args) const { return func(std::forward<Args>(args)...); }
    
    //! Invoke the callback with the supplied arguments.
    R invoke(const Args & ... args) const { return (*func)(args...); }
    
    //! Releases the callback function pointer.
    void clear()
    {
        func.reset();
    }

    //! \return true if callback function pointer is null.
    bool is_null()
    {
        return !func;
    }


private:
    FunctionPointer func; //!< Function container.

    //!< Helper class to *actually* call the *extended* function.
    template<class UserData, R(*Function)(Args..., UserData)>
    static R function_caller_e(Args && ... args, UserData userdata) {
        return (*Function)(std::forward<Args>(args)..., userdata);
    }

    //!< Helper class to *actually* call the member function.
    template<class C, R(C::*CMethod)(Args...)>
    static R method_caller(C* instance, Args && ... args) {
        return (instance->*CMethod)(std::forward<Args>(args)...);
    }

    //!< Helper class to *actually* call the *extended* member function.
    template<class C, class UserData, R(C::*CMethod)(Args..., UserData)>
    static R method_caller_e(C* instance, Args && ... args, UserData userdata) {
        return (instance->*CMethod)(std::forward<Args>(args)..., userdata);
    }
};

/** Helper macro for creating callbacks from class methods.
 *
 *  \code
 *  // We want to bind a callback to the member function `int Foo::bar(float)`
 *  // of an instance of `Foo` called `meow` (i.e. `Foo meow;`).
 *  //
 *  // - The function call signature is `int(float)`.
 *  // - The class name is `Foo`.
 *  // - The method name is `bar`.
 *  // - The instance name is `meow`.
 *
 *  auto cb = MAKE_METHOD_CALLBACK(int(float), Foo, bar, meow)
 *
 *  // The macro is expanded to this:
 *  // ( Callback<int(float)>( ).set<Foo, &Foo::bar>( meow ) )
 *  // X ^[1]^^^^^^^^^^^^^^^^^^^ ^[2]^^^^^^^^^^^^^^  ^[3]^^  X
 *  // 1. Create a Callback for a function that takes a `float` and returns an `int`.
 *  // 2. Set the callback to call the member function of a certain class `Foo` called `Foo::bar`.
 *  // 3. Bind an instance of `Foo` called `meow` to the callback.
 *  // X. Evaluate the return type, which is a `Callback<int(float)>&`
 *
 *  int x = cb.invoke(3.142f); // Invokes `meow.bar(3.142f)`.
 *  \endcode
 *
 *  \param call_sig Basic function call signature. e.g. `int(float)`
 *  \param cls      Class type name. e.g. `Foo`
 *  \param method   Class method / member function name. e.g. `bar`
 *  \param instance Class object to bind to this callback.
 */
#define MAKE_METHOD_CALLBACK(call_sig, cls, method, instance) \
    (Callback<call_sig>().set<cls, &cls::method>(instance))

/** Helper macro for creating callbacks from extended class methods.
 *
 *  \code
 *  // ... same scenario as MAKE_METHOD_CALLBACK but with a different function type.
 * 
 *  auto cb = MAKE_METHOD_CALLBACK_E(int(size_t), void*, Foo, alloc, meow, buff)
 *
 *  // The macro is expanded to this:
 *  // ( Callback<int(float)>( ).set<Foo, void*, &Foo::bar>( meow, buff ) )
 *  
 *  int x = cb.invoke(3.142f); // Invokes `meow.alloc(1024, buff)`.
 *  \endcode
 *
 *  \param call_sig Basic function call signature **excluding** the last parameter,
 *                  which should be `ud_t`. (e.g. `int(size_t)`)
 *  \param ud_t     User data type name.
 *  \param cls      Class type name. e.g. `Foo`
 *  \param method   Class method / member function name. e.g. `alloc`
 *  \param instance Class object to bind to this callback.
 *  \param userdata Instance of userdata to bind to this callback.
 */
#define MAKE_METHOD_CALLBACK_E(call_sig, ud_t, cls, method, instance, userdata) \
    (Callback<call_sig>().set<cls, ud_t, &cls::method>(instance, userdata))

////    Testing class
struct Data {
    int z;
};

class Foo {
public:
    Foo() {}
    void   print() { std::cout << "void Foo::print" << std::endl; }
    int   rprint() { std::cout << "int Foo::rprint(), ( ret = " << -3142 << " )" << std::endl; return -3142; }
    void  pprint(int x) { std::cout << "void Foo::pprint(int x), ( x = " << x << " )" << std::endl; }
    void mpprint(int x, float y) { std::cout << "void Foo::pprint(int x), ( x = " << x << ", y = " << y << " )" << std::endl; }
    int   cprint(int x) { std::cout << "int Foo::cprint(int x), ( x = " << x << " )" << std::endl; return x; }
    int  mcprint(int x, float y) { std::cout << "int Foo::mcprint(int x, float y), ( x = " << x << ", y = " << y << " )" << std::endl; return x; }
    int  udprint(int x, Data* u) { std::cout << "int Foo::udprint(int x, Data u), ( x = " << x << ", u.z = " << u->z << " )" << std::endl; return u->z; }
};

int gprint(int x, float y) { std::cout << "int gprint(int x, float y), ( x = " << x << ", y = " << y << " )" << std::endl; return x; }
int dprint(int x, Data* u) { std::cout << "int dprint(int x, Data* u), ( x = " << x << ", u.z = " << u->z << " )" << std::endl; return u->z; }

void main() {
    Foo* foo = new Foo();
    auto c1 = MAKE_METHOD_CALLBACK(void(), Foo, print, foo);
    auto c2 = Callback<int ()          >::from_method<Foo, &Foo:: rprint>(foo);
    
    auto c3 = Callback<void(int)       >::from_method<Foo, &Foo:: pprint>(foo);
    auto c4 = Callback<void(int, float)>::from_method<Foo, &Foo::mpprint>(foo);
    auto c5 = Callback<int (int)       >::from_method<Foo, &Foo::cprint>(foo);
    auto c6 = Callback<int (int, float)>::from_method<Foo, &Foo::mcprint>(foo);
    
    c1.invoke();
    c2.invoke();
    c3.invoke(123);
    c4.invoke(321, 34.0f);
    c5.invoke(321);
    c6.invoke(321, 12.0f);

    auto cc = c3;
    cc.invoke(987);

    auto cg = Callback<int(int, float)>(&gprint);
    cg.invoke(123, 23.0f);

    auto cu = Callback<int(int)>::from_method_e<Foo, Data*, &Foo::udprint>(foo, new Data{ 4 });
    cu.invoke(123);

    auto cd = Callback<int(int)>::from_function_e<Data*, &dprint>(new Data{ 6 });
    cd.invoke(123);
}