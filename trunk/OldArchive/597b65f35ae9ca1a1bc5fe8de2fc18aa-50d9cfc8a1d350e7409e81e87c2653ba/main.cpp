#include <iostream>
#include <string>
#include <vector>

struct the_api_thing {
    int x;
};

void f(the_api_thing* thing, void(*callback)(the_api_thing*)) {
    callback(thing);
}

int main()
{
    struct with_my_stuffs : the_api_thing {
        int y;
    } object;
    object.y = 42;
    
    f(&object, [](the_api_thing* x) {
        auto p = static_cast<with_my_stuffs*>(x);
        std::cout << p->y;
    });
}
