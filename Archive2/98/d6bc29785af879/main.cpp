#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct {
    void operator() (const string& s) { cout << "String: " << s << '\n'; }
    void operator() (int n) { cout << "Integer: " << n << '\n'; }
    void operator() (double d) { cout << "Double: " << d << '\n'; }
} print;

template<typename Func>
void unpack_data(const string& data, Func call_on_token)
{
    istringstream data_stream(data);
    for (char c; data_stream >> c;)
        switch (c) {
            case 's': {
                string s;
                data_stream >> s;
                call_on_token(s);
            } break;
            
            case 'i': {
                int n;
                data_stream >> n;
                call_on_token(n);
            } break;
            
            case 'd': {
                double d;
                data_stream >> d;
                call_on_token(d);
            } break;
        }
}

int main()
{
    unpack_data("i12 sAdira d15.87", print);
}
