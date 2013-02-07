#include <iostream>
#include <thread>
#include <string>

int main()
{
    using namespace std;
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();
    string s1 = "penguin";
    string s2, s3;
    cout << "YOU CAN ASSIGN A STRING OBJECT TO ANOTHER: S2 = S1" << endl;
    s2 = s1;
    cout << "s1 = " << s1 << " s2 = " << s2 << endl;
    cout << "YOU can assign a c style string to a string object." << endl;
    cout << "s2 = \"buzzard\"\n";
    s2 = "buzzard";
    cout << "s2 = " << s2 << endl;
    cout << "you can concatenate strings: s3 = s1 + s2" << endl;
    s3 = s1 + s2;
    cout << "s3 = " << s3 << endl;
    cout << "you can append string." << endl;
    s1 += s2;
    cout << "s1 += s2 yields s1 = " << s2 << endl;
    s2 += " for a day";
    cout << " s2 += \" for a day\" yields s2 = " << s2 << endl;
    return 0;
}
