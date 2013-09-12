#include <iostream>
#include <memory>
#include <stdlib.h>
using namespace std;
class Tester
{
private:
    int _i;    
public:
    Tester()
    {
        cout << "Tester::ctor()" << endl;
        _i = rand();
    }
    Tester(const Tester& other)
    {cout << "Tester::ctor(const Tester&)" << endl;}
    ~Tester()
	{cout << "Tester::dtor()" << endl;}
    void Print()
    {cout << "Hello World: " << _i << endl;}
};
int main()
{
	shared_ptr<Tester> s1(new Tester()); //Create new shared_ptr
	cout << "Use count [1]: " << s1.use_count() << endl;
	{
		shared_ptr<Tester> s2 = s1;
		cout << "Use count [2]: " << s1.use_count() << endl;
        {
            shared_ptr<Tester> s3 = move(s2);
            cout << "Use count of s2 [1]: " << s2.use_count() << endl;
            cout << "Use count of s3 [1]: " << s3.use_count() << endl;
            s2->Print();
        }
        cout << "Use count of s2 [2]: " << s2.use_count() << endl;
        if (s2)
            s2->Print();
	} //s2 & s3 go out of scope here
	cout << "Use count [4]: " << s1.use_count() << endl;
} //s1 goes out of scope here, thus deleting the object