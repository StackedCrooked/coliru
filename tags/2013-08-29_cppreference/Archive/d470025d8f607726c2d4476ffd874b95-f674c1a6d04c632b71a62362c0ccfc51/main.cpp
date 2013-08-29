template <typename T> void foo()
{
    T instance = T(); // default constructor
}

int main() {
    foo<int>();
    int instance = int();
}