#include <cstdlib>
#include <isotream>
using namespace std;

int main() {
char* as = new char[100];
    as[0] = 'a';
    as[1] = 'b';
    as[2] = NULL;
    cout << as << endl;
}