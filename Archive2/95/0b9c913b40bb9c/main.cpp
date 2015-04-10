template<int N>
struct Int;

template<typename Scrutinee, typename... Cases>
struct Switch {};

template<typename Val, typename Clause>
struct Case;

int main()
{
    using result_type =
        Switch< Int<2>
              , Case< Int<1>, bool>
              , Case< Int<2>, float>
              , Case< Int<3>, int>
        >;
    
    result_type r [[gnu::unused]];
}