struct easy
{
    enum : int { a = 5 };
    int b;

    constexpr easy(int b_) : b(b_<a? a : b_)
    {}
};

int main() {
    static const easy peasy { 42 };
}