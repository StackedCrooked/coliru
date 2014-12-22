template <typename type>
using r_ptr = type *__restrict__;

void foo(r_ptr<int>)
{}

int main()
{
    int x = 0;
    foo(&x);
}
