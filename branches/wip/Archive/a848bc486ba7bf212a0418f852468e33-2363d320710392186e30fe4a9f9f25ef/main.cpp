#include <string.h>

struct Blob {
    char data[128];
};

// Use long name so that will be easy to spot in the asm output.
Blob __Ext__get_blob__Ext__();
void __Ext__set_blob__Ext__(const Blob&);


INLINE void __Int__modify__Int__(Blob& blob)
{
    unsigned n;
    char* byte = &blob.data[sizeof(n)];
    memcpy(&n, byte, sizeof(n));
    n = 42;
    memcpy(byte, &n, sizeof(n));
}

int main()
{
     auto b = __Ext__get_blob__Ext__();
     __Int__modify__Int__(b);
     __Ext__set_blob__Ext__(b);    
}