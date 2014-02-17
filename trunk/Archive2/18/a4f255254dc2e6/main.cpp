#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>


bool getYesNoResponse()
{
    string response;
    getline (cin, response);
    while (response.size() == 0 ||
    (response[0] != 'y' && response[0] != 'Y'
     && response[0] != 'n' && response[0] != 'N'))
    {
        if (response.size() > 0)
        cout << "Please respond 'yes' or 'no'. " << flush;
        getline (cin, response);
    }
    return response[0] == 'y' || response[0] == 'Y';
}
