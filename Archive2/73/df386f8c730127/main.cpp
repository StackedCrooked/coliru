#include<iostream>

using namespace std;

template<typename type>
    struct ugaw //uninitialized temporary generator and array wrapper
    {
        ugaw() {}

        ugaw(const ugaw&) = default;

        ugaw(const type & arg) { *this = *(const ugaw*)arg; } //data-only copy constructor (doesn't invoke any 'type' functions)

        & operator type() & {return d;} //cast operator for a reference to 'type' (used for arrays)

        & operator const type() const & {return d;} //cast operator for a const reference to 'type' (used for arrays)

        ugaw & operator =(const ugaw&) = default;

        ugaw & operator =(const type &arg) { *this = *(const ugaw*)arg; } //data-only assignment operator

        type *operator & () & { return &d; } //address operator to return the actual data stored

        const type *operator & () const & { return &d; } //and a constant version

        type d;
    };

ugaw<int [4]> FuncAdd(ugaw<int [4]> arg_0, const ugaw<int [4]> arg_1)
{
    for(size_t i(0); i < sizeof(arg_0) / sizeof(arg_0[0]); ++i)
        arg_0[i] += arg_1[i];

    return arg_0;
}
    
int main()
{
    int var[4]{0, 1, 2, 3};

    int var1[4]{1, 1, 2, 3};

    auto &&refArray = FuncAdd(var, var1);

    for(size_t i(0); i < sizeof(var) / sizeof(var[0]); ++i)
        cout << var[i] << endl;

    cout << "Here" << endl;

    for(size_t i(0); i < sizeof(var1) / sizeof(var1[0]); ++i)
        cout << var1[i] << endl;

    cout << "Here" << endl;

    for(size_t i(0); i < sizeof(refArray) / sizeof(refArray[0]); ++i)
        cout << refArray[i] << endl;
    
    return 0;
}