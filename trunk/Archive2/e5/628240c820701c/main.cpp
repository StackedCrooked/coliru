#include <iostream>
#include <memory>
#include <functional>

namespace detail
{
    // int sequence
    template<int ...> struct seq {};
    // int seq generator
    template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};
    template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };
}

template<typename T>
    class Delegate { };

template<typename RetType, typename Instance, typename... ArgTypes>
class Delegate<RetType(Instance*, ArgTypes...)>
{
    public:
        using return_type = RetType;
        using fn_type = std::function<RetType(Instance *, ArgTypes...)>;
        
        Delegate(Delegate const & other) = delete;

        Delegate(Delegate &&other) :
            mFn(other.mFn),
            mArgs(other.mArgs) // hmm
        { 
        }

        // member function wrapper
        Delegate(RetType(Instance::*mem_func)(ArgTypes...), ArgTypes... args) :
            mFn(std::mem_fn(mem_func)),
            mArgs(std::make_tuple(std::forward<ArgTypes>(args)...))
        { }

        Delegate& operator=(Delegate const &) = default;

        RetType operator()(Instance* ins)
        {
            if(!mFn) throw 0;
            return callDelegate(ins, typename detail::gens<sizeof...(ArgTypes)>::type());
        }

    private:
        template<int ... S>
            RetType callDelegate(Instance* ins, detail::seq<S...>) 
            {
                return mFn(ins, std::get<S>(mArgs)...);
            }
        
        fn_type mFn;
        std::tuple<ArgTypes...> mArgs;
};

/* Event, a delegate wrapper */
template<typename Ret, typename I, typename... Args>
struct Event 
{
    using DelegateType = Delegate<Ret(I*, Args...)>;

    DelegateType del;
    I* instance;
    
    Event(DelegateType &del, I* instance) :
        del(std::move(del)),
        instance(instance)
    {}
    
    /* Fires the event */
    Ret fire() { return del(instance); }


    static Event<Ret, I, Args...> createEvent(Delegate<Ret(I*, Args...)> &fn, I* instance)
    {
        return std::move(Event<Ret, I, Args...>(fn, instance));
    }
};


struct Bar {
    virtual ~Bar() { } 
    virtual int bb(int x, int y) { return y+x;}
};

struct Baz : Bar {
    int bb(int x, int y) { return x*y; }
};


int main(void)
{
    Bar b{};
    Baz z{};
    
    // Construct and call delegate
    Delegate<int(Bar*, int, int)> del(&Bar::bb, 32, 1000);
    std::cout << del(&b) << std::endl;
    
    // Construct Event using ctor
    auto e = Event<int, Bar, int, int>(del, &b);
    std::cout << e.fire() << std::endl;

    auto ee = Event<int, Bar, int, int>(del, &z);
    std::cout << ee.fire() << std::endl;
}
