#include <inttypes.h>
#include <utility>
using std::forward;

struct outDev
{
    template<typename Signature> struct call;
    template<typename Func, typename... Args> struct call<Func(Args...)>
    {
    
        typedef Func (*functor_t)(void *const, Args &&...);
        const functor_t functor;

        template<class Class, Func (Class::* const ptr)(Args...)>
        static constexpr Func stub(void *const objectPtr, Args &&... args)
        {
            return (static_cast<Class *const>(objectPtr)->* ptr)(forward<Args>(args)...);
        }

        constexpr call(functor_t fn) noexcept : functor(fn) { }

    public:
        call() = delete;
        constexpr call(const call &c) noexcept : functor(c.functor) { }
        constexpr call(call &&c) noexcept : functor(c.functor) { }

        template<class Class, Func (Class::* const ptr)(Args...)>
        constexpr static call make() noexcept
        {
            return call(stub<Class, ptr>);
        }

        constexpr Func operator ()(void *const object, Args... args) const noexcept
        {
            return functor(object, forward<Args>(args)...);
        }
    };

    typedef call<int(const uint32_t baud)> init_t;

    struct functions
    {
    public:
        const init_t init;

        constexpr functions() = delete;
        constexpr functions(functions &&fns) noexcept : init(fns.init) { }
        constexpr functions(const functions &fns) noexcept : init(fns.init) { }
        constexpr functions(const init_t initFn) noexcept : init(initFn) { }
    };
    const functions *const vtable;
    void *const instance;

    constexpr outDev(const functions *const table, void *const inst) noexcept : vtable(table), instance(inst) { }

public:
    void init(const uint32_t baud) noexcept { vtable->init(instance, baud); }
};

struct out_t : public outDev
{

    int initDev(const uint32_t) noexcept { return 0; }
    static constexpr outDev::functions const table[1] = { outDev::init_t::make<out_t, &out_t::initDev>() };

public:
    constexpr out_t() noexcept : outDev(&table[0], this) { }
};

#include <cstdio>


int main(int, char **)
{
    out_t dev;
    dev.init(115200);
    printf("fuck!\n");
    return 0;
}