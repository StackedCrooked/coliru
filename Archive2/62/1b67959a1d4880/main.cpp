#include <fstream>
#include <algorithm>
#include <iterator>
#include <crypto++/blowfish.h>
#include <crypto++/modes.h>
#include <iostream>

static std::vector<byte> const key { 's','e','c','r','e','t' };
static byte const SIGNATURE[] = "ABCD"; //{ 'A','B','C','D' };

int main()
{
    if (std::ofstream data {"test.bin", std::ios::binary})
    {
        data.write((const char*) SIGNATURE, 4);
        std::vector<byte> plaintext { std::istreambuf_iterator<char>(std::cin), {} };

        // write the actual size (without padding)
        uint32_t length = plaintext.size();
        data.write(reinterpret_cast<char*>(&length), sizeof(length)); // TODO use portable byte-order

        // ensure padding
        while (plaintext.size() % 32)
            plaintext.push_back(0); // TODO replace with proper crypto padding!
        
        assert(data.good() || data.eof());

        CryptoPP::ECB_Mode<CryptoPP::Blowfish>::Encryption encryption(key.data(), key.size());

        std::vector<char> ciphertext(plaintext.size());

        encryption.ProcessData(reinterpret_cast<byte*>(ciphertext.data()), plaintext.data(), plaintext.size());

        data.write(ciphertext.data(), ciphertext.size());
    } else
    {
        return 1; //Error opening file
    }
}
