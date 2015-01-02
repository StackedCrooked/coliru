#include <iostream>
#include <memory>
#include <tuple>


struct Probe
{
    template<typename ...Args>
    void apply(std::tuple<Args...>& tuple)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};


struct type_erased_tuple
{
    template<typename ...Args>
    type_erased_tuple(const std::tuple<Args...>& inTuple) :
        mImpl(new Impl<Args...>(inTuple))
    {
    }
    
    void apply(Probe& probe)
    {
        mImpl->apply(probe);
    }
    
    struct Base
    {
        virtual ~Base() {}
        
        virtual void apply(Probe& probe) = 0;
    };
    
    template<typename ...Args>
    struct Impl : Base
    {
        template<typename Tup>
        Impl(Tup&& tup) : mTuple(std::forward<Tup>(tup)) {}
        
        virtual void apply(Probe& probe)
        {
            probe.apply(mTuple); // or something
        }
        
        std::tuple<Args...> mTuple;
    };
    
    std::shared_ptr<Base> mImpl;
};


int main()
{
    type_erased_tuple softuple(std::make_tuple(1, 2.0, false));
    
    Probe probe;
    softuple.apply(probe);
}

