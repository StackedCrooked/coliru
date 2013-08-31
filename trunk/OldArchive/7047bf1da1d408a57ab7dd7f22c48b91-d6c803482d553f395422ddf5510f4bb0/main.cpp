struct S {

friend void fn(S& s) { }

S() {
fn(*this);
}
};

int main()
{
    S s;
    auto c = s;
}