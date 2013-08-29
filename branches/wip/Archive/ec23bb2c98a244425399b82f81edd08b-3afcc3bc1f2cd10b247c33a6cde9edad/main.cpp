void foo(const int &) {}

int main() {
    int i;
    int &r = i;
    foo(r);
}