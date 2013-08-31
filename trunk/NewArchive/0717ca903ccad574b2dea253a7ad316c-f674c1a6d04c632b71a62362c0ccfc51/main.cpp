#include<string>
#include<exception>
#include<type_traits>
using namespace std;

class A : public exception {
public:
    A(string msg) : _msg(msg) {}
    //~A() throw(){};
    const char* what() const throw() { return _msg.c_str();}
private:
    string _msg;
};

int main()
{
    int val = is_nothrow_destructible<std::string>();
    printf("%d",val);
}
