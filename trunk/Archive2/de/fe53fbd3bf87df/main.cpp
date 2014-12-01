void func() {}

int main()
{
    void* s = reinterpret_cast<void*>(func);
    reinterpret_cast<decltype(func)>(s);
}
