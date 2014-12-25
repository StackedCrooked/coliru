#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class ExStream {
private:
    string val;
public:
    ExStream() {};
    friend ExStream& operator<<(ExStream& ex, string s) {
        ex.val.append(s);
        return ex;
    }
    operator string() {
        return val;
    }
};

void func(string s) {
    cout << "Output: " << s << endl;
}

int main() {
    ExStream ex;
    ex << "This is a test.";
    func(ex);            // Works just fine!
    func((string)ex);    // Error: 'Conversion': 'ExStream' cannot
                         // be cast into 'std::string'
}