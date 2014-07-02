#include <iostream>
#include <cstring>

using namespace std;

char* mystrtok_r  ( char *str, const char *delim, char **nextp)
{
    char *ret;

    if (str == nullptr)
    {
        str = *nextp;
    }

    str += std::strspn(str, delim);

    if (*str == '\0')
    {
        return nullptr;
    }

    ret = str;

    str += std::strcspn(str, delim);

    if (*str)
    {
        *str++ = '\0';
    }

    *nextp = str;

    return ret;
}


int main( int argc, char* argv[] )
{

    char *str1, *str2, *token, *subtoken;
    char *saveptr1, *saveptr2;
    int j;

   /* This piece is copied from http://linux.die.net/man/3/strtok_r */
   if (argc != 4) {
        std::cerr <<"Usage: %s string delim subdelim\n"<<
                argv[0] ;
        return -1;
    }

   for (j = 1, str1 = argv[1]; ;  j++, str1 = nullptr ) {
        token = mystrtok_r(str1, argv[2], &saveptr1);
        if (token == nullptr)
            break;
        
        std::cout << j << " :" << token << endl;
       for (str2 = token; ; str2 = nullptr) {
            subtoken = mystrtok_r(str2, argv[3], &saveptr2);
            if (subtoken == nullptr)
                break;
            std::cout << " -->" << subtoken << endl ;
        }
    }
}
