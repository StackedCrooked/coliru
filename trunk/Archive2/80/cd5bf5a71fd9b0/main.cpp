class R;
namespace N {
    template <class T> void test(const T& rec);
    template<> void test<R>(const R&);
}

class R {
    friend void N::test(const R&);  // 8
    int m;
};

template<> void N::test<R>(const R& rec) { rec.m; }

int main() {
    R r;
    N::test(r);
}