int main()
{
    auto make_counter = [](int i = 0) { return [i]() mutable { return i++; }; };
    auto c = make_counter();
    return c();
}