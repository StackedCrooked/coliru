extern const int foo[];
const int foo[] = { 42, 13, 1 };

int main() {
    const_cast<int&>(foo[0]) = 0;
}