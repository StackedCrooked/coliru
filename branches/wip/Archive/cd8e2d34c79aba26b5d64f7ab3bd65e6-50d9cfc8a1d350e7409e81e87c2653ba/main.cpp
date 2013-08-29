class a { virtual ~a(); };

class b : a {};

class c : a {};

int main() {
    c one;
    a* two = &one;
    auto x = dynamic_cast<b*>(two);
}