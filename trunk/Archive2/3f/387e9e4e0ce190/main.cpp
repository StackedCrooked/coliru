struct A
{
    A(A&&) = delete;
    A(A const&) = delete;
};

struct B;

template<class T>
T dv();

int main(int argc, char** argv) {
    using T = decltype(dv<A>());
    using U = decltype(dv<B>());
    return 0;
}