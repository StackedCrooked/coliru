#include <iostream>
#include <string>
using namespace std;

template <char... Chs>
struct MyStruct
{
    string d_text;
    MyStruct() : d_text({Chs...}){}
};

int main()
{
    cout << MyStruct<'a','b'>().d_text << '\n';
    return 0;
}
