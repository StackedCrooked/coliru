template <class T> struct identity {using type = T;};

template <typename T>
struct FunctionAnalyzer
    : identity<decltype(&T::operator())> {};

int main()
{
    []
    {
        auto a = []{};
        using b = FunctionAnalyzer<decltype(a)>::type;
        b _; (void)_; // to avoid warnings
    }();
}