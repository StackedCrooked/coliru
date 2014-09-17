#include <iostream>

struct NoDefCtor
{
    NoDefCtor() = delete;
    NoDefCtor(int){}
};

template<typename T>
struct MyList
{
    T &get(std::size_t index, T &def = default_value()){return def;}

private:
    static T &default_value()
    {
        static T t;
        return t;
    }
};

int main()
{
    MyList<NoDefCtor> list;
    NoDefCtor def {0};
    auto &v = list.get(100, def);
}
