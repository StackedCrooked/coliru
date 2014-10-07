#include <cstdio>
 
int main ()
{
    // write buffer to file
    std::FILE *f1;
    char buffer[] = { 'x' , 'y' , 'z' };
    f1 = std::fopen("file.bin", "wb");
    std::fwrite(buffer, sizeof(char), sizeof(buffer), f1);
    std::fclose(f1);
 
    // read the same data and print it to the standard output
    std::FILE *f2;
    char rbuf[10];
    f2 = std::fopen("file.bin", "rb");
    const char* res = std::fgets(rbuf, sizeof(rbuf), f2);
    std::fclose(f2);
 
    if (res) { // points to rbuf on read success, NULL on failure
        std::puts(res);
    }
}