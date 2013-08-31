#include <type_traits>

struct Timer { };
int main()
    {
    int time_keeper(Timer());
    static_assert(
        std::is_same<
            decltype(time_keeper), 
            int(Timer(*)())
        >::value, 
        "This should not fire!");
}