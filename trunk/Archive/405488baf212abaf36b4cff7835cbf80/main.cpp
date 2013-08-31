struct first{};
struct second{};

struct origin{
    operator first(){ return {}; }
    operator second() const{ return {}; }
};

void foo(first);
void foo(second);

int main()
{
    foo(origin{});
}