#include <string>

namespace details
{
    template <typename PolicyImpl>
        struct PolicyFactory
        {
            static PolicyImpl Create() {
                return {};
            }
        };
}

template <typename>
struct Policy2 { Policy2(double) { } };

template <typename T,
          typename P1 = Policy2<T> >
struct X 
{
    X()      : _policy1(details::PolicyFactory<P1>::Create()) {}
    X(P1 p1) : _policy1(std::move(p1)) { }

  private:
    P1 _policy1;
};

///// supply a factor, possibly local to a TU:

namespace details
{
    template <typename T>
        struct PolicyFactory<Policy2<T> > {
            static Policy2<T> Create() { 
                return Policy2<T>(3.14);
            }
        };
}

int main()
{
     // with a factory:
     X<std::string, Policy2<std::string> > no_params_because_of_factory;
}
