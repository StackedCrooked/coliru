struct cat
{
    cat() = default;
    cat(cat const&) = default;
    cat(cat&&) = delete;
};

cat meow() { return cat{}; }
cat purr() { return static_cast<cat&&>(cat{}); }

int main()
{
    auto kitten = meow();
    auto grumpy = purr();
}