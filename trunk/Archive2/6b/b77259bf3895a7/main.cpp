#include <memory>
#include <utility>
#include <iostream>

template<typename PARTICLE_DATA>
struct type_erased_policy
{
public:
    template<class P> // SFINAE to make it less greedy
    type_erased_policy(P&& p)
        : _policy(std::make_shared<policy_impl<P>>(std::forward<P>(p)))
    {}
    
    void operator()( PARTICLE_DATA& data )
    {
        (*_policy)( data );
    }

    void step()
    {
        _policy->step();
    }

private:
    struct policy_interface
    {
        virtual ~policy_interface() {}

        virtual void operator()( PARTICLE_DATA& data ) = 0;
        virtual void step() = 0;
    };

    template<typename POLICY>
    class policy_impl : public policy_interface
    {
    public:
        policy_impl(POLICY p)
            : _policy(std::move(p))
        {}
        
        void operator()( PARTICLE_DATA& data ) override
        {
            _policy( data );
        }

        void step() override
        {
            step(0);
        }

    private:
        POLICY _policy;
        
        template<class T = POLICY>
        auto step(int) -> decltype(std::declval<T&>().step())
        { _policy.step(); }
        
        void step(short)
        {}
    };

    std::shared_ptr<policy_interface> _policy;
};

struct policy
{
    void operator()(int)
    { std::cout << "policy::operator()\n"; }
    void step()
    { std::cout << "policy::step\n"; }
};

int main()
{
    int i = 42;
    type_erased_policy<int> p0([](int){std::cout << "lambda\n";});
    p0(i);
    p0.step();
    type_erased_policy<int> p1(policy{});
    p1(i);
    p1.step();
}