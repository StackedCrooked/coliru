#include <string.h>

struct Blob { char data[128]; };


Blob get_blob();
void set_blob(const Blob&);

// We compile first with -DINLINE=inline and then
// with -DINLINE='' and compare the assembly output.
INLINE void modify_blob(Blob& blob)
{
    unsigned n;
    char* byte = &blob.data[sizeof(n)];
    memcpy(&n, byte, sizeof(n));
    n = 42;
    memcpy(byte, &n, sizeof(n));
}

int main()
{
     auto b = get_blob();
     modify_blob(b);
     set_blob(b);    
}