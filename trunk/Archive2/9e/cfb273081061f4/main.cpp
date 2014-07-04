#include <iostream>
#include <utility>

//move this somewhere useful later
template<typename... Args>
void swallow(Args&&...)
{
}

//and this

template<typename... Args>
void dbgprint(Args &&... args)
{
   swallow((std::cout << std::forward<Args>(args), 0)...);
}

int main() {
    dbgprint(1, ' ', 2, " foo ", 5, '\n', "yay");   
}