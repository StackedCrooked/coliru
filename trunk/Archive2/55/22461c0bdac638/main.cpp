#include<iostream>


char *pCreateString(const char *, size_t, size_t);

using namespace std;

int main()
{
    const char chArray[] { "SubString" };

    char *pResult;

    cout << (pResult = pCreateString(chArray, 3, 6)) << endl; //store function result in 'pResult' and cout it

    delete[] pResult; // free memory, allocated by 'pCreateString'

    return 0;
}


char *pCreateString(const char *pString, size_t szFrom, size_t szNChars)
{
    char *pTmp = new char[szNChars + 1]; // allocate sizeof(char) * szNChars + 1 bytes

    //store the sub-string

    for(size_t i(0); i < szNChars; ++i)
        pTmp[i] = pString[i + szFrom];

    pTmp[szNChars] = '\0'; //store the terminating 'null-character'

    return pTmp;
}
