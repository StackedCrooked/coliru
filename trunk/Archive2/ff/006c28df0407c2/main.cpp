// detail1
namespace detail {
    void f() {}
};

void g() {
    // static scoping knows this is detail1
    detail::f();
}

delete namespace detail;

// detail2
namespace detail {
    void f() {}
};

void h() {
    // static scoping knows this is detail2
    detail::f();
}

delete namespace detail;


int main(int argc, char** argv) {
    return 0;
}