#include <string>
#include <type_traits>

using namespace std;

//NOTE: this class is just an example to demonstrate the problem
class String {
    public:
        //default constructor to prevent ambiguity
        String() {}

        //construct from wstring
        template<typename Args>
        String(Args&& args, typename enable_if<is_constructible<wstring, Args>::value,int>::type = 0) : ws(forward<Args>(args)) {}

        //construct from string
        template<typename Args>
        String(Args&& args, typename enable_if<is_constructible<string, Args>::value,int>::type = 0) : s(forward<Args>(args)) {}

private:
        string s;
        wstring ws;
};

int main()
{
    String a(L"123");
    String b("123");
    return 0;
}
