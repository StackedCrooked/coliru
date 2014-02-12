#include <iostream>

struct Context {}; // stub

struct IRule
{
    virtual ~IRule() {}
    virtual void Begin(int value) = 0;
    virtual double Evaluate(Context& context) = 0;
};

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/accumulate.hpp>
#include <boost/phoenix.hpp>

namespace phx = boost::phoenix;
namespace fus = boost::fusion;
using namespace phx::arg_names;

template<typename Rules>
class CompositeRule : public IRule
{
    Rules m_rules;
  public:
    CompositeRule(Rules rules) : m_rules(rules) {}

public:
    virtual void Begin(int value)
    {
        fus::for_each(m_rules, phx::bind(&IRule::Begin, arg1, value));
    }

    virtual double Evaluate(Context& context)
    {
        return fus::accumulate(m_rules, 0.0, arg1 + phx::bind(&IRule::Evaluate, arg2, phx::ref(context)));
    }
};

void DoSomething(IRule& rule)
{
    static Context ctx;

    rule.Begin(2);
    std::cout << "Sum of Evaluate: " << rule.Evaluate(ctx) << "\n";
}

struct RuleA : IRule { /* concrete implementation */
    RuleA(double v = 3.14) : _val(v), _x(0) {} double _val, _x; 
    void Begin(int x)                 { /*std::cout << __PRETTY_FUNCTION__ << "\n";*/ _x = x;         }
    double Evaluate(Context& context) { /*std::cout << __PRETTY_FUNCTION__ << "\n";*/ return _val*_x; }
};

int main()
{
    CompositeRule<boost::tuple<RuleA, RuleA, RuleA> > combine(boost::make_tuple(RuleA(20), RuleA(), RuleA(100)));

    DoSomething(combine);
}
