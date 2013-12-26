template <unsigned int N>
struct foo : protected foo<N - 1> {
protected:
    enum {number = N};
public:
    constexpr int at(const unsigned int index) {
        //static_assert(index <= N, "out of range");
        //return this->foo<index>::number;
        return number;
    }
};

template <>
struct foo<0> {
protected:
    enum {number = 0};
public:
    constexpr int at(const unsigned int index) {
        //static_assert(index == 0, "out of range");
        //return this->number;
        return number;
    }
};

int main() {
    foo<5> f5;
    static_assert( f5.at(123) != 5, "equals 5");
}