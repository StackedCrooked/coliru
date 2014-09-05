#include <cstdio>

auto terminal = [](auto term)            // <---------+  
{                                        //           |
    return [=] (auto func)               //           |  ???
    {                                    //           |
        return terminal(func(term));     // >---------+
    };
};


auto main() -> int
{
    auto hello =[](auto s){ fprintf(s,"Hello\n"); return s; };
    auto world =[](auto s){ fprintf(s,"World\n"); return s; };


    terminal(stdout)
            (hello)
            (world) ;

    return 0;

}
