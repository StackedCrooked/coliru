template<typename T>
void nil(T) {zzz}

template<typename T>
void foo(T*) {}

int main()
{
    int* blah;
    foo(blah);
}