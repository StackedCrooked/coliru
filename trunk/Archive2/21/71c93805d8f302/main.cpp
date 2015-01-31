#include <utility>

class test{
public:
    test(int);
    test(const test&);
    test& operator=(test rhs);
    test(test&&);
    test& operator=(test&& rhs);
private:
    int *p = nullptr;
};

test::test(int i): p(new int(i)){}

test::test(const test& rhs): p(new int(*rhs.p)){}

test& test::operator=(test rhs) {
    using std::swap;
    swap(*this, rhs);
    return *this;
}

test::test(test&& rhs): p(rhs.p){rhs.p = nullptr;}

test& test::operator=(test&& rhs) {
    p = rhs.p;
    rhs.p = nullptr;
    return *this;
}
