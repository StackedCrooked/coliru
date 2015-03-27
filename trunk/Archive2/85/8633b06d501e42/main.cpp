struct S{};
constexpr S s1{};
constexpr S s2;

struct test{
    static constexpr auto t1 = s1;
    static constexpr auto t2 = s2;  //error here
};