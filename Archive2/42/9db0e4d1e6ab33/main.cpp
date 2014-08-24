//Author Manu Sánchez (Manu343726). Aug 2014

//Everything started from this: http://stackoverflow.com/questions/25338795/is-there-a-name-for-this-tuple-creation-idiom
//Now, play with C++14!

#include <utility>
#include <iostream>

auto tuple = [](auto... args)
{
    return [=](auto f){ return f(args...); };  
};

auto map = [](auto... args, auto fn)
{
    return tuple(fn(args)...);
};

auto cat = [](auto... l1, auto... l2)
{
    return l1([=](auto... v1s) {
        return l2([=](auto... v2s) {
            return tuple(v1s..., v2s...);
        });
    });
};


int main()
{
    map(tuple(1,2,3), [](auto val) {
        std::cout << val << std::endl;
    });
}