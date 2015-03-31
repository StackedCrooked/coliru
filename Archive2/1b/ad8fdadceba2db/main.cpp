#include <cstdio>

class c {
public:
    explicit c(bool flag) : flag(flag) { }

    void f() {
        if (flag) {
            std::printf("f\n");
        }
    }

    void g() {
        if (!flag) {
            std::printf("g\n");
        }
    }

private:
    bool flag;
};

int main() {
    c x(true);
    x.f();
    x.g();
    c y(false);
    y.f();
    y.g();
    return 0;
}