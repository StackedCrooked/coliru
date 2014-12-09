#include <iostream>
#include <utility>

template <typename Arg, typename... Args>
void doPrint(std::ostream& out, Arg&& arg, Args&&... args)
{
    std::cout << std::forward<Arg>(arg);
    using expander = int[];
    (void)expander{0, (void(std::cout << "," << std::forward<Args>(args)),0)...};
}

int main()
{
    doPrint(std::cout, 34, "bla", 15);
}
