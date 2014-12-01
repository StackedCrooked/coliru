void f() {}

int main()
{
    void* s = reinterpret_cast<void*>(f);
	auto p = reinterpret_cast<decltype(f)*>(s);
}
