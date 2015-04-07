template <typename T> struct S { };

template <template <typename> class TT, typename T> struct S2 { };

template <template <template <typename> class, typename> class TTT, template <typename> class TT, typename T> S3 { };

int main() {
    S3<S2, S, int> s;
}