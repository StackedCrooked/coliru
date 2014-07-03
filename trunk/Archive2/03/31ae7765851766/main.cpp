struct prefix
{
    prefix& operator--() { return *this; }
    prefix& operator++() { return *this; }
};

struct any : prefix
{
    using prefix::operator--;
    using prefix::operator++;
    any operator--(int) { return any(); }
    any operator++(int) { return any(); }
};

int main() {

    any a;

    a--;
    a++;
    --a;
    ++a;

    return 0;
}