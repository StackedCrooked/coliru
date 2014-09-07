struct A
{
    A(A&&) = delete;
    A(A const&) = delete;
};

template<class T>
T dv();

int main(int argc, char** argv) {
    using T = decltype(dv<A>());
    return 0;
}