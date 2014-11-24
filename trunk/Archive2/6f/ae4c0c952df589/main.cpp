
template<typename T> struct TD;

template<typename ... Args> struct Tuple {};

template <class First, class ... Rest>
struct Tuple<First, Rest ...> {

        Tuple() {}
        Tuple(First const& _first) : first(_first) {}
        Tuple(First const& _first, Tuple<Rest ...> const& _rest) : first(_first), rest(_rest) {}

        First first;
        Tuple<Rest ...> rest;
};

template<typename First, typename ... Args>
auto make_tuple(First const& first, Args const& ... args)
{
    return Tuple<First, Args ...>(first, make_tuple(args ...));
}

template<typename First>
auto make_tuple(First const& first)
{
    return Tuple<First>(first);
}


double evaluate(int a) { return static_cast<double>(a); }

template<typename First, typename ... Args>
auto evaluate(Tuple<First, Args ...> const& t)
{
    return make_tuple(evaluate(t.first), evaluate(t.rest));
}

template<typename First>
auto evaluate(Tuple<First> const& t)
{
    return Tuple<decltype(evaluate(t.first))>(evaluate(t.first));
}

int main()
{
    Tuple<int,int> t;
    t.first=1;
    t.rest.first=2;
    
    auto s=evaluate(t);
    
    TD<decltype(s)>();
}

