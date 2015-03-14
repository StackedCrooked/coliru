#include <sstream>
#include <string>

using namespace std;

#define EMPTY 0
#define STREET_MAX
#define INVALID -1

int main() {
    string street;
    int result;
    
     if (street == "") {
        result = EMPTY;
    } else if (street.length() > STREET_MAX) {
        result = INVALID;
    } else {
        stringstream ss(street);
    }
}