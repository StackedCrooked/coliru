#include <memory>
#include <iostream>
#include <tuple>

template <typename... Args>
struct foo
{
    static void call(Args&&... args)
    {
        baz(std::forward<Args>(args)...);
    }

    static void baz(Args&&... args)
    {
        auto tup = std::make_tuple(std::forward<Args>(args)...);
        auto val = std::get<0>(std::move(tup));
        ++val.i;
    }
};
   
struct s
{
    static int count_move_cons;
    static int count_move_assign;
    int i;
 
    s() : i(0) { }
    ~s() = default;
    s(const s&) = delete;
    s& operator=(const s&) = delete;
    s(s&&) { ++count_move_cons; }
    s& operator=(s&&) { ++count_move_assign; return *this; }
};

int s::count_move_cons = 0;
int s::count_move_assign = 0;

int main()
{
    foo<s>::call(s{});
    std::cout << "Move construction: " << s::count_move_cons << "\n";
    std::cout << "Move assignment: " << s::count_move_assign << "\n";
} 