int main()
{
    auto l = [] () noexcept { throw 42; };
    try { l(); } catch (...) { }
}
