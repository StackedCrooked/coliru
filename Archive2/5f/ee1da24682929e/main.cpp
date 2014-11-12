#include <string>
 
double f[3]; // zero-initialized to three 0.0's
int* p;   // zero-initialized to null pointer value
std::string s; // zero-initialized to indeterminate value
               // then default-initialized to ""
int main(int argc, char* argv[])
{
    static int n = argc; // zero-initialized to 0
                         // then copy-initialized to argc
    delete p; // safe to delete a null pointer
}