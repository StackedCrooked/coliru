struct a { virtual ~a() {} };

struct b : a {};

struct c : a {};

int main() {
    c one;
    a* two = &one;
    auto x = dynamic_cast<b*>(two);
}