template<typename F, typename Result, typename ...Params>
Result concrete_wrapper(const void *f, Params... params)
{
    return (*static_cast<const F*>(f))(params...);
}

template<typename Signature>
class function_non_owning;

template<typename Result, typename ...Params>
class function_non_owning<Result(Params...)>
{
    const void *f = nullptr;
    Result (*wrapper)(const void *, Params...) = nullptr;
public:
    function_non_owning() = default;

    template<typename F>
    function_non_owning(const F &f)
        : f(&f), wrapper(&concrete_wrapper<F, Result, Params...>)
    {}

    Result operator()(Params... params) const
    {
        return wrapper(f, params...);
    }
};

// Example of usage:

void baz(function_non_owning<int(int, int)> x)
{
    volatile auto y = x(111, 222) + 555;
    (void)y;
}

void test_baz()
{
    baz([](int x, int y){ return x+y; });
}
