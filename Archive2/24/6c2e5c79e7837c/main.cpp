template<int N>
class Foo {
    bool bar() {
        if (N == 0)
            return true;
        return 5 / N == 1;
    }
};

Foo<0> bar;

int main(){}
