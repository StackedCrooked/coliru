
class base {};
class derived : public base {};

void test(const base& x)
{
    auto& k = static_cast<const derived&>(x);
}

int main()
{
    derived k;
    test(k);
}