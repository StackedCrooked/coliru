
struct Item
{
    Item(int a, int b = 1) : a(a), b(b) {}
    int a, b;
};


void foo (Item)
{
}


int main()
{
    foo(0);
}