#include <iostream>
#include <fstream>
#include <string>

/*
this-is-a-string foo boo doo goo
this-is-a-string foo boo doo goo
this-is-a-string foo boo doo goo
this-is-a-string foo boo doo goo
*/

int main()
{
    std::ifstream InFile( __FILE__ ) ;

    std::string strCommand;
    while( InFile >> strCommand )
    {
        if (strCommand == "this-is-a-string" )
        {
            std::streampos nFilePosition = InFile.tellg();

            std::streamoff offset = nFilePosition ;

            std::cout << "offset: " << offset << '\n' ;

            //foo(strFilename, nFilePosition);
        }

        InFile.ignore(1000, '\n');
    }
}

/*
this-is-a-string foo boo doo goo
this-is-a-string foo boo doo goo
this-is-a-string foo boo doo goo
this-is-a-string foo boo doo goo
*/
