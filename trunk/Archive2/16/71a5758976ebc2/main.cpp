#include  <iostream>
#include  <utility>
#include  <array>

class abc_t
{
public:
    void testA(int n)
    {
        switch (n)
        {
        case 1:
            testA<1>();
            break;
        case 2:
            testA<2>();
            break;
        }
    }
    template <int N>
    void testA()
    {
        std::cout << "testA: N = " << N << std::endl;
    }

    template <int N>
    void testB()
    {
        std::cout << "testB: N = " << N << std::endl;
    }

    template<std::size_t... I>
    void testA_(std::size_t n, std::index_sequence<I...> s) {
        static constexpr std::array<void (abc_t::*)(), sizeof...(I)> a{&abc_t::template testA<I>...};
        if (n < a.size())
            (this->*a[n])();
    }

    void testA2(int n) {
        testA_(n, std::make_index_sequence<10>());
    }

    void testB2(int n) {
        // ti porta a riscrivere testB_, non c'e' soluzione.senza qualche aiutino dal preprocessore.
    }
};

int main(int argc, char *argv[])
{
    abc_t abc;
    abc.testA(2);
    abc.testA2(4);
}
