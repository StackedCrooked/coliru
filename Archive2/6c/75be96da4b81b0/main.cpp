#include <cstdio>

auto terminal = [](auto term)            // <---------+  
{                                        //           |
    return [=] (auto func)               //           |  ???
    {                                    //           |
        return terminal(func(term));     // >---------+
    };
};

/*
terminal(stdout) -returns> anonymous_lambda which captures stdout (functor)
anonymous_lambda(hello) is called, func(term) is hello(stdout) and prints "Hello" and returns stdout, the anonymous_lambda -returns> terminal(stdout)
(the above 2 lines start again)
terminal(stdout) is called and -returns> anonymous_lambda which captures stdout (functor)
anonymous_lambda(world) is called, func(term) is world(stdout) and prints "World" and returns stdout, the anonymous_lambda -returns> terminal(stdout)
terminal(stdout) is called and -returns> anonymous_lambda which captures stdout (functor)
nobody uses that anonymous_lambda.. end.
*/

auto main() -> int
{
    auto hello =[](auto s){ fprintf(s,"Hello\n"); return s; };
    auto world =[](auto s){ fprintf(s,"World\n"); return s; };

    world(hello(stdout));
    
    
    terminal(stdout)
            (hello)
            (world) ;

    return 0;

}