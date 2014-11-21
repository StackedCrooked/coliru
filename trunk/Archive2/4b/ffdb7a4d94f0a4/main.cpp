#include <iostream>

struct tmp_buf
{
    char arr[24];
    ~tmp_buf() { std::cout << " [~] "; }
};

const char* foo(int id, tmp_buf&& buf = tmp_buf())
{
    sprintf(buf.arr, "foo(%X)", id);
    return buf.arr;
}

void try_stomp()
{
    double d = 22./7.;
    char buf[32];
    snprintf(buf, sizeof(buf), "pi=%lf", d);
    std::cout << "\n" << buf << "\n";
}

int main()
{
    std::cout << "at call site: " << foo(123456789);
    std::cout << "\n";

    std::cout << "after call site: ";
    const char* p = foo(123456789);

    try_stomp();

    std::cout << p << "\n";
    return 0;
}