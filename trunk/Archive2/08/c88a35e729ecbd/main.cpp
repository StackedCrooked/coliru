namespace N {
    template <class T> void test(const T& rec) { rec.m; }
}

template <class T>
class R {
    friend void N::test(R<T> const&);  // 8
    int m;
};

int main() {
    R<int> r;
    N::test(r);
}