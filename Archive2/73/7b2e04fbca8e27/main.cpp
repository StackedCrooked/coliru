
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


template<typename First, typename ... Args, typename FunctionType>
auto evaluate(Tuple<First, Args ...> const& t, FunctionType f)
{
    return make_tuple(f(t.first), evaluate(t.rest, f));
}

template<typename First, typename FunctionType>
auto evaluate(Tuple<First> const& t, FunctionType f)
{
    return Tuple<decltype(f(t.first))>(f(t.first));
}

int main()
{
    Tuple<int,int> t;
    t.first=1;
    t.rest.first=2;
    
    auto yourCustomFunction= [](auto x) {return static_cast<double>(x);};
    
    auto s=evaluate(t, yourCustomFunction);
    
    //TD<decltype(s)>();  //display new type, uncomment if you want
                        // it prints Tuple<double, Tuple<double>, so is not exactly what you want
                        // otherwise, i.e. for "Tuple<double,double>", you'd need something like "tuple_cat"
}

