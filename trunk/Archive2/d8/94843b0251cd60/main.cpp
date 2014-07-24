#include <string>
 
double f[3]; // zero-initialized to three 0.0's
std::string s; // zero-initialized to indeterminate value
               // then default-initialized to ""
int main(int argc, char**)
{
    int* p;   // zero-initialized to null pointer value
    static int n = argc; // zero-initialized to 0
    printf("n er %d \n", n);
    printf("p er %p \n", (void*)p);
    (void)n;
                         // then copy-initialized to argc
    delete p; // safe to delete a null pointer
}