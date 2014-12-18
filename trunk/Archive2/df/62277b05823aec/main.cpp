


struct Items
{
    char data[6];
};


Items get();
void set(const Items&);




void test()
{
    set(get());
}