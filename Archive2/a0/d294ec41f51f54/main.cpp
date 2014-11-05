#include <iostream>
#include <map>
#include <memory>
#include <string.h>
using namespace std;

int main(int argc, char *argv[]) {
    char buf[1024 * 32];
    auto buf2 = make_unique<char[]>(1024 * 32);

    {
        memset(buf, 0, sizeof buf);
        FILE *f = fopen("tmpfile", "wb");
        printf("write = %d\n", fwrite(buf, 1, sizeof buf, f));
        fclose(f);
    }

    //char*p = 0 ? buf2.get() : buf;
    //char*p = buf;
    char*p = buf2.get();

    FILE *f = fopen("tmpfile", "r+b");

    printf("read = %d\n", fread(p, 1, sizeof buf, f));

    fclose(f);
    return 0;
}