#include <functional>
#include <string>
#include <algorithm>

class Foo 
{
    public:

    template<typename T = char>
    bool Moo(std::function<bool()> f = [](){ return true; }) const
    {
        std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
        str2.erase(std::remove_if(str2.begin(), str2.end(),
                        [](char x){return true;}), str2.end());
        // just to do something
        f = 0;
        return f();
    };
};

int main(int argc, char **args) 
{
    Foo* myFoo = new Foo();
    return myFoo->Moo<>();
}