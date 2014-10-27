struct not_a_unique_ptr {
    not_a_unique_ptr() = default;
    
    not_a_unique_ptr(not_a_unique_ptr&&) = default;
    not_a_unique_ptr& operator=(not_a_unique_ptr&&) = default;
};

struct S {

    S(int X = 0, int Y = 0):x(X), y(Y){}

    int x;

	int y;

};

struct S2 {
    S2(int X = 0, int Y = 0):x(X), y(Y){}

    S2(const S2&) {}
    S2& operator=(const S2&) { return *this; }

    int x;
    int y;
    not_a_unique_ptr ptr;
};

int main()
{
    S a;
    auto copy = a;
    
    S2 b;
    auto yes_a_copy = b;
}