#include <cstdio>
#include <iostream>

using namespace std;

const size_t szArrayBounds = 260;

size_t FindStrInStr(const char *, const char *);

int main()
{
    const char str[szArrayBounds] { "String" };

    const char str1[szArrayBounds] { "ing"};

    cout << &(str[FindStrInStr(str, str1)]); //Testvane na funciqta
}

size_t FindStrInStr(const char *pString_Target, const char *pString_To_Search)
{
    if(pString_Target == NULL || pString_To_Search == NULL)
        return -1;

    for(size_t i(0); i < szArrayBounds && pString_Target[i]; ++i)
    {
        bool bWasDiffFound = false;

        for(size_t y(0); y < szArrayBounds && pString_To_Search[y]; ++y)
        {
            if(pString_To_Search[y] != pString_Target[i + y])
            {
                bWasDiffFound = true;

                break;
            }
        }

        if(!bWasDiffFound)
        {
            return i;
        }
    }

    return -1; 
}

