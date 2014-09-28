#include <iostream>
#include <string>

using namespace std;

class GetReadFile {
public:
    // Function Declaration
    template <size_t R, size_t C>   // Template same as definition
    bool writeHistory(double writeArray[R][C], string path);
};

// Function Definition
template <size_t R, size_t C>      // Template same as declaration
bool GetReadFile::writeHistory(double writeArray[R][C], string path) {
    return true;
}

int main()
{
    GetReadFile grf;
    double array[5][8];
    
    grf.writeHistory(array,"blah");
    cout  << "OK!" << endl;
}
