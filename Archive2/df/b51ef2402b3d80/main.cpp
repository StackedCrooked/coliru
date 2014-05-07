#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <crypto++/blowfish.h>
#include <crypto++/modes.h>

using namespace std;
using namespace CryptoPP;

int main()
{
    string file = "C:\\test.bin";    

    byte *header = new byte[32];

    FILE *data = fopen(file.c_str(), "r");

    if(data == NULL)
    {
        return 1; //Error opening file!
    }

    char type[6];

    type[5] = 0;

    if(fread(type, sizeof(type) - 1, 1, data) < 1)
    {
        return 2;
    }

    if(strcmp(type, "ABCD") != 0)
    {
        return 3;
    }

    if(fread(header, sizeof(header), 1, data) < 1)
    {
        return 2; //Error reading file!
    }

    vector<byte> key;

    key.push_back(0xAA);
    key.push_back(0xBB);
    key.push_back(0xCC);
    key.push_back(0xDD);
    key.push_back(0xAA);
    key.push_back(0xBB);
    key.push_back(0xCC);
    key.push_back(0xDD);

    ECB_Mode<Blowfish>::Decryption decryption(key.data(), key.size());

    byte out[32];

    decryption.ProcessData(out, header, 32);

    FILE *outer =  fopen("C:\\out.bin", "w");

    fwrite (out, sizeof(byte), sizeof(out), outer);
}
