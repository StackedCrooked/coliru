typedef unsigned long size_t;
struct B{};

B operator+(B, B) { return B(); }
B operator"" _b(const char *, size_t) { return B(); }

template<typename T>
class C
{
    friend B operator+(B, B);
    friend B operator"" _b(const char *, size_t);
};

int main() { return 0; }
