template<typename F>
auto fix(F f) {
    return f(f);
}

struct F {
    int operator()(F const& f) const {
        return f(f);
    }
};

int main() {
    fix(F());
    return 0;
}
