template<typename... bounded_types>
struct variant {
    static_assert(sizeof...(bounded_types) > 0, "empty variant is illegal");
};

int main() {
    variant<>();
    return 0;
}
