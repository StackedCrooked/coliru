#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

int main() {
    string parameters = "Greg";
    system(("ps -ef|grep " + parameters).c_str());
}
