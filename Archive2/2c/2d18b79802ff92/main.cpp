#include <boost/mpl/push_back.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace boost;

bool read_runtime_bool()
{
    return rand() % 2 == 1;
}

template<typename State=mpl::vector<>, int Count, typename F>
void read_compile_time_bools(mpl::int_<Count>, F f)
{
    if(read_runtime_bool() == true)
        read_compile_time_bools<typename mpl::push_back<State, mpl::true_>::type>(mpl::int_<Count-1>{}, f);
    else
        read_compile_time_bools<typename mpl::push_back<State, mpl::false_>::type>(mpl::int_<Count-1>{}, f);
        
}

template<typename State, typename F>
void read_compile_time_bools(mpl::int_<0>, F f)
{
    f(State{});
}

int main()
{
    srand(time(0));

    read_compile_time_bools(mpl::int_<5>{}, [](auto bools)
    {
        mpl::for_each<decltype(bools)>([](auto flag)
        {
            constexpr bool compile_time_bool = decltype(flag)::value;
            static_assert(compile_time_bool == true || compile_time_bool == false, "");
            cout << compile_time_bool << endl;
        });
    });
}
