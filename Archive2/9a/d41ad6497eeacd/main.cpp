template <class Head, class... Tail>
class tuple {};

template<typename... Values>
void f(tuple<Values...> const& rhs) {}

int main() {
    tuple<int, float> t;
    f(t);
}