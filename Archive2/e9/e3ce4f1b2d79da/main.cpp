#include <iostream>
#include <functional>

#define VER 1

#if VER == 0
#define FIRST int
#define SECOND std::function<int(int)>
#elif VER == 1
#define FIRST auto
#define SECOND std::function<int(int)>
#elif VER == 2
#define FIRST int
#define SECOND auto
#else
#define FIRST auto
#define SECOND auto
#endif

auto terminal = [](FIRST term)       // <---------+  
{                                    //           |
    return [=] (SECOND func)         //           |  ???
    {                                //           |
        return terminal(func(term)); // >---------+
    };
};

int main()
{
    terminal(2)( [](int x) { std::cout << x << "\n"; return x; } );
}