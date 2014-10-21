void foo() {
    // some code ...
    int* i(new int);
    int* j = new(int);
    // ... more code
    //delete i and j
}

int main()
{
    foo();
}