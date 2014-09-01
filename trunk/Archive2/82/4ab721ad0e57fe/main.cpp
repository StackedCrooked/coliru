#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

unsigned int decrypt(unsigned char *encBuffer, unsigned int encBufferLen, unsigned char *decBuffer)
{
  unsigned int decBufferLen = 0;

  unsigned char table[] = { NULL, ' ', '-', '.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0x0D };

  unsigned int offset = 0, i = 0;
  unsigned char encStrLen = 0, c = 0;

  while (offset < encBufferLen)
  {
    if (encBuffer[offset] == 0xFFU) // if byte is 0xFF then add 0x0D to new buffer and continue
    {
      *(decBuffer + decBufferLen++) = 0x0D;
      offset++;
      continue;
    }

    encStrLen = encBuffer[offset++]; // get string length

    i = 0;
    if ((encStrLen & 0x80U) == 0) // if result is 0 then decrypt the string by Xor 33
    {
      while ((i++ < encStrLen) && (offset < encBufferLen))
      {
        *(decBuffer + decBufferLen++) = (encBuffer[offset++] ^ 0x33U);
      }
    }
    else // otherwise
    {
      encStrLen &= 0x7FU;
      while ((i < encStrLen) && (offset < encBufferLen))
      {
        c = encBuffer[offset++]; // c = current byte, increment the index
        *(decBuffer + decBufferLen++) = (table[(c & 0xF0U) >> 4]);

        if (table[c & 0x0FU] != NULL)
        {
          *(decBuffer + decBufferLen++) = table[c & 0x0FU];
        }

        i += 2;
      }
    }
  }

  return decBufferLen;
}

std::vector<unsigned char> encrypt(std::vector<unsigned char> decryptedBuf) {
  vector<unsigned char> result;

  size_t cur_offset = 0;
  while (cur_offset < decryptedBuf.size()) {
    unsigned char chunk_size = static_cast<unsigned char>(
        min(decryptedBuf.size() - cur_offset, size_t(0x7F)));
    result.push_back(chunk_size);
    result.insert(result.end(), decryptedBuf.begin() + cur_offset,
                  decryptedBuf.begin() + cur_offset + chunk_size);

    for (vector<unsigned char>::iterator it = result.end() - chunk_size;
         it != result.end(); ++it) {
      *it ^= 0x33;
    }

    cur_offset += chunk_size;
  }
  return result;
}

int main(){
  const char plaintext[] = "Hello world\r\n .1234567890";
  vector<unsigned char> v_plaintext(
      (unsigned char*)plaintext,
      (unsigned char*)(plaintext + sizeof(plaintext)));
  vector<unsigned char> v_cyphertext = encrypt(v_plaintext);

  vector<unsigned char> decrypted(2 * v_cyphertext.size());
  unsigned int decrypted_size =
      decrypt(&v_cyphertext.front(), v_cyphertext.size(), &decrypted.front());
  decrypted.resize(decrypted_size);

  cout << "Original: " << plaintext << endl;
  cout << "Decrypted: " << (char*)(&decrypted.front()) << endl;
  return 0;
}