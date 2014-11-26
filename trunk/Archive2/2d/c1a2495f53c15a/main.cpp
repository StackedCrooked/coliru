template<typename>
struct S {};

int main() {
    S<S<int>> s;   
}