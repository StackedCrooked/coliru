int* f() { return new int; }

template <class T>
using generic_pointer = auto (*)() -> T*;

int main()
{
    generic_pointer<int> p = &f;
};