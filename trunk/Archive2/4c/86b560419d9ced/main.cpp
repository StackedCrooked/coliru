#include <iostream>

using namespace std;

struct s1 { char a; };
struct s2 { char a; char b; };
struct s3 { char a; int b; };
struct s4 { char a; int b; char c; };
struct s5 { char a; char b; int c; };

int main() {
cout << "sizeof(char): " << sizeof(char) << endl;
cout << "sizeof(char*): " << sizeof(char*) << endl;
cout << "sizeof(char**): " << sizeof(char**) << endl;
cout << "sizeof(unsigned char): " << sizeof(unsigned char) << endl;
cout << "sizeof(unsigned char*): " << sizeof(unsigned char*) << endl;
cout << "sizeof(unsigned char**): " << sizeof(unsigned char**) << endl;
cout << "sizeof(short): " << sizeof(short) << endl;
cout << "sizeof(short*): " << sizeof(short*) << endl;
cout << "sizeof(short**): " << sizeof(short**) << endl;
cout << "sizeof(unsigned short): " << sizeof(unsigned short) << endl;
cout << "sizeof(unsigned short*): " << sizeof(unsigned short*) << endl;
cout << "sizeof(unsigned short**): " << sizeof(unsigned short**) << endl;
cout << "sizeof(int): " << sizeof(int) << endl;
cout << "sizeof(int*): " << sizeof(int*) << endl;
cout << "sizeof(int**): " << sizeof(int**) << endl;
cout << "sizeof(unsigned int): " << sizeof(unsigned int) << endl;
cout << "sizeof(unsigned int*): " << sizeof(unsigned int*) << endl;
cout << "sizeof(unsigned int**): " << sizeof(unsigned int**) << endl;
cout << "sizeof(long): " << sizeof(long) << endl;
cout << "sizeof(long*): " << sizeof(long*) << endl;
cout << "sizeof(long**): " << sizeof(long**) << endl;
cout << "sizeof(unsigned long): " << sizeof(unsigned long) << endl;
cout << "sizeof(unsigned long*): " << sizeof(unsigned long*) << endl;
cout << "sizeof(unsigned long**): " << sizeof(unsigned long**) << endl;
cout << "sizeof(long long): " << sizeof(long long) << endl;
cout << "sizeof(long long*): " << sizeof(long long*) << endl;
cout << "sizeof(long long**): " << sizeof(long long**) << endl;
cout << "sizeof(unsigned long long): " << sizeof(unsigned long long) << endl;
cout << "sizeof(unsigned long long*): " << sizeof(unsigned long long*) << endl;
cout << "sizeof(unsigned long long**): " << sizeof(unsigned long long**) << endl;
cout << "sizeof(float): " << sizeof(float) << endl;
cout << "sizeof(float*): " << sizeof(float*) << endl;
cout << "sizeof(float**): " << sizeof(float**) << endl;
cout << "sizeof(double): " << sizeof(double) << endl;
cout << "sizeof(double*): " << sizeof(double*) << endl;
cout << "sizeof(double**): " << sizeof(double**) << endl;

cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PART TWO~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

cout << "siizeof(s1): " << sizeof(s1) << endl;
cout << "siizeof(s1*): " << sizeof(s1*) << endl;
cout << "siizeof(s1**): " << sizeof(s1**) << endl;
cout << "siizeof(s2): " << sizeof(s2) << endl;
cout << "siizeof(s2*): " << sizeof(s2*) << endl;
cout << "siizeof(s2**): " << sizeof(s2**) << endl;
cout << "siizeof(s3): " << sizeof(s3) << endl;
cout << "siizeof(s3*): " << sizeof(s3*) << endl;
cout << "siizeof(s3**): " << sizeof(s3**) << endl;
cout << "siizeof(s4): " << sizeof(s4) << endl;
cout << "siizeof(s4*): " << sizeof(s4*) << endl;
cout << "siizeof(s4**): " << sizeof(s4**) << endl;
cout << "siizeof(s5): " << sizeof(s5) << endl;
cout << "siizeof(s5*): " << sizeof(s5*) << endl;
cout << "siizeof(s5**): " << sizeof(s5**) << endl;

return 0;
}
