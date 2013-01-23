#include <iostream>

class puzzle
{
public:
    puzzle(int x) : x(x) {}

    int get_x() const
    {
        return x;
    }

private:
    puzzle& operator=(const puzzle&);

    int x;
};

namespace detail
{
    template <typename Victim, typename Value, Value Victim::*Pointer>
    struct thief
    {
        static auto steal(Victim& instance)
        -> decltype(instance.*Pointer)&
        {
            return instance.*Pointer;
        }
    };

    template <typename T>
    struct decay { typedef T type; };
}

#define STEAL(Instance, Name) \
    [&Instance] () \
    -> typename detail::decay< \
            decltype(detail::decay< \
                decltype(Instance) \
            >::type::Name \
        )>::type& \
    { \
        using Victim = decltype(Instance); \
        using Type = typename detail::decay<decltype(Victim::Name)>::type; \
        return detail::thief<Victim, Type, &Victim::Name>::steal(Instance); \
    } ()

int main()
{
    puzzle solution(42);
    std::cout << "before: " << solution.get_x() << '\n';
    STEAL(solution, x) = 666;
    std::cout << "after: " << solution.get_x() << std::endl;
}
