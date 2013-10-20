#include <string>

using namespace std;

//NOTE: this class is just an example to demonstrate the problem
class String {
    public:
        //default constructor to prevent ambiguity
        String() {}

    private:
        //construct from wstring
        template<typename... Args, class = typename enable_if<is_constructible<wstring, Args...>::value, void>::type>
        String(int, Args&&... args) : ws(forward<Args>(args)...) {}

        //construct from string
        template<typename... Args, class = typename enable_if<is_constructible< string, Args...>::value, void>::type>
        String(int&&, Args&&... args) : s(forward<Args>(args)...) {}
        
    public:
        template<typename... Args>
        String(Args&&... args) : String(0, forward<Args>(args)...) {}
        
    private:
        string s;
        wstring ws;
};

int main()
{
    static_assert(is_constructible<string, char const(&)[4]>{}, "!");
    String a(L"123");
    String b("123");
    return 0;
}