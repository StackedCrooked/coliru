#include <utility>

bool g_profiling;
template<class wrapfunc_type, class return_type, class...Ps>
void record(wrapfunc_type wrapfunc, return_type ret, Ps...Vs)
{
    ...?
}


template<class signature, signature func> struct Wrap;

template<class R, class...Ps, R(&func)(Ps...)> 
struct Wrap<R(Ps...), func>
{
    typedef R(&signature)(Ps...);
    typedef R return_type;
    typedef std::tuple<Ps...> parameters;
    
    R operator()(Ps...Vs) const
    {
        auto result = func(Vs...);
        if (g_profiling) record(*this, result, Vs...);
        return result;
    }
};
        
#define WRAP(X) Wrap<decltype(X),X>()

int main() {
    HANDLE hnd = 3;
    WRAP(CloseHandle)(hnd);
}