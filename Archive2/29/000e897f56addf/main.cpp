template <class _T>
void inc(int &x) {
    x++;
}

template <class FUNC>
void add(int &x, FUNC f) {
    f(x);
}

int main() {
    int x = 0;
    add(x, inc<int>);
    return 0;
}