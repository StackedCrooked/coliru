#include <cstdio>
#include <iostream>

using namespace std;

const size_t szArrayBounds = 260;

size_t FindStrInStr(const char (&)[szArrayBounds], const char (&)[szArrayBounds], bool &);

int main()
{
    const char str[szArrayBounds] { "String" };

    const char str1[szArrayBounds] { "ing"};

    bool bSuccess;

    cout << &(str[FindStrInStr(str, str1, bSuccess)]); //Testvane na funciqta
}

size_t FindStrInStr(const char (&pString_Target)[szArrayBounds], const char (&pString_To_Search)[szArrayBounds], bool &bSuccess) // zabele6i syntaxisa na argumentite - te biha prieli samo masivi s opredelena dal6ina (v slu4aq 'szArrayBounds')
{
    //Nqma nu6da ot proverka za 'nullptr' (ili nulev ukazatel) tai kato predavame masivite po referenciq (reference)

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
            bSuccess = true;
            return i;
        }
    }

    bSuccess = false;

    return size_t(); //vra6ta vremenen obekt inicializiran po default (toest s '0') = sa6toto kato - 'return 0',
    // ne e dobra ideq da se saob6tava za gre6ka 4rez vra6tane na '-1', tai kato tova sa6to e validen index na masiv za tova tretiq argument trqbva da e promenliva ot tip 'bool', koqto 6te se proverqva za gre6ka
}

