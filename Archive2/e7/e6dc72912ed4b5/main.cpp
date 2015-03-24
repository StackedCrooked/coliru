template <int a, int b>
struct Test
{
   static constexpr double c = a / b;
};

int main() {
    static_assert(Test<10, 2>::c == (double)5);
}