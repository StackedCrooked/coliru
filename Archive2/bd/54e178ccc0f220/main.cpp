#include <initializer_list>
#include <iostream>

struct foo {
    int i;
    foo(std::initializer_list<std::initializer_list<int>> list) {
        for (const auto & row : list) {
            for (const auto & elem : row) {
                std::cout << elem << ", ";
            }
            std::cout << '\n';
        }
        std::cout << "Juchu\n";
    }
    /*
    foo & operator,() (const foo & rhs) {
        i += rhs.i;
        return *this;
    }
    //friend foo& operator+=(const foo& lhs, const foo& rhs);
    /
    foo & operator+=(const foo & rhs) {
        i += rhs.i;
        return *this;
    }
    */
};

void test(const foo & a, const foo & b) {
    std::cout << a.i << ", " << b.i << '\n';
}

foo& operator+=(foo& lhs, const foo& rhs)
{
    lhs.i += rhs.i;
    return lhs;
}

int main() {
    foo bar{
        {5, 6}
        ,{5, 4}
    };
    /*
    foo baz{7};
    std::cout << bar.i << '\n';
    bar += baz;
    std::cout << bar.i << '\n';
    */
}