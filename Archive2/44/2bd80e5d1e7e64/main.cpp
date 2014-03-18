struct source;

struct dest
{
    dest(source);
};

struct source
{
    operator dest() const;
};

void foo(dest);
void foo(...);

int main()
{
    auto s = source{};
    foo(s);
}