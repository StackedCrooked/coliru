#include <iterator>
#include <vector>
#include "match.hpp"

struct widget {};
struct gadget {};

void draw(widget) { println("drawing widget"); }
void draw(gadget) { println("drawing gadget"); }

int main()
{
    using namespace std;
    bool flags[] = {true, false, true, true, false};
    vector<variant<widget, gadget>> xs;
    
    for(auto f : flags)
        if(f)
            xs.push_back(widget{});
        else
            xs.push_back(gadget{});

    for(auto x : xs)
        MATCH(x)
            CASE(x IS _) { draw(x); }
        ;
    println();

    vector<variant<int, double>> ys;
    for(auto x : xs)
        ys.push_back
        (
            MATCH(x)
                CASE(x IS widget) { println("x IS widget"); return 1; }
                CASE(x IS gadget) { println("x IS gadget"); return 0.1; }
        );
    println();

    for(auto y : ys)
        MATCH(y)
            CASE(y IS int)    { println("y IS int"); }
            CASE(y IS double) { println("y IS double"); }
        ;
}
