#include <sstream>
#include <iostream>
 
int main()
{
    using std::cout;
    using std::endl;
    cout << std::boolalpha;
    
    std::istringstream s1("Hello, world.");
    char c1 = s1.get(); // reads 'H'
    cout << "after reading " << c1 << ", gcount() == " <<  s1.gcount() << '\n';
    char c2;
    s1.get(c2);         // reads 'e'
    char str[5];
    s1.get(str, 5);     // reads "llo,"
    cout << "after reading " << str << ", gcount() == " <<  s1.gcount() << '\n';
    cout << c1 << c2 << str;
    s1.get(*cout.rdbuf()); // reads the rest, not including '\n'
    cout << "\nAfter the last get(), gcount() == " << s1.gcount() << '\n';
    cout << (bool)s1 << endl;

    cout << "eof == " << s1.eof() << endl;
    cout << "good == " << s1.good() << endl;
    cout << "fail == " << s1.fail() << endl;
    cout << "bad == " << s1.bad() << endl;
    
    int aa = s1.get();
    cout << "aa == " << aa << ", gcount() == " << s1.gcount() << endl;
    
    
    
}