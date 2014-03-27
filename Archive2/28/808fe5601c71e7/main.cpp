#include <cstddef>
class S;
int main()
{
    int* p = NULL;
    int* p2 = static_cast<std::nullptr_t>(NULL);
    void(*f)(int) = NULL;
    int S::*mp = NULL;
    void(S::*mfp)(int) = NULL;
}