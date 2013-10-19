template<class T> class R;
namespace N {
    template <class T> void test(const T& rec);
    template<> void test<R<int>>(const R<int>&);
}

template <class T>
class R {
    friend void N::test(const R<int>&);  // 8
    int m;
};

template<> void N::test<R<int>>(const R<int>& rec) { rec.m; }

int main() {
    R<int> r;
    N::test(r);
}