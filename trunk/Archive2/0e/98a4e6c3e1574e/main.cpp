template <unsigned T>
constexpr auto fact() {
    if(T==1)
        return 1;
    return T*fact<T-1>();
}

int main(void) {
    static_assert(fact<3>()==6,  "fact doesn't work");
}
