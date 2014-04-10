#include <functional>
#include <iostream>
using namespace std;

using cmdf = function<void()>;
template <typename T> using alias = T;

int main()
{
    struct _ { cmdf undo, redo; } static const cmd { []{cout<<"pain";}, []{cout<<"relief";} };

    for (int i=1; i<100000; i*=42)
        (cmd.*alias<cmdf _::*[]>{&_::undo,&_::redo }[rand()%2])();
}
