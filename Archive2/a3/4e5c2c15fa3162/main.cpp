#include <iostream>  
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sstream>

using namespace std;

int main()
{;
    int arraylen = 7, arraylen_new = 0, i = 0, nextstep = 0;
    string line, field, junkText;
    string* randNum = new string[arraylen];
    string* phrase = new string[arraylen];

    ifstream randomTxt;
    arraylen = 5;

    randomTxt.open("random.txt");

    while(!randomTxt.eof())
    {
        getline(randomTxt,line);
        std::cout << "DEBUG OUTER: '" << line << "'\n";
        stringstream ss(line);
        nextstep = 0;
        while(getline(ss,field,','))
        {
            std::cout << "DEBUG INNER: " << i << " '" << field << "'\n";
            /*if(nextstep == 0)
            {
                randNum[i] = field;
                cout<< "number " << i << ": " << randNum[i] << endl;
                nextstep = 1;
            }

            else if(nextstep == 1)
            {
                junkText = field;
                cout<< "junk " << i << ": " << junkText << endl;
                nextstep = 2;               
            }
            else
            {
                items[i] = field;
                cout<< "items " << i << ": " << items[i] << endl;
            }*/

            if(i == (arraylen-1))
            {
                arraylen_new = arraylen + 1;
                string* temp1 = new string[arraylen_new];
                string* temp2 = new string[arraylen_new];
                copy(randNum, (randNum+arraylen), temp1);
                delete [] randNum;
                randNum = temp1;

                copy(phrase, (phrase + arraylen), temp2);
                delete [] phrase;
                phrase = temp2;
                arraylen = arraylen_new;
            }
        }
        i++;
    }    
    randomTxt.close();

    /*for(int i = 0; i < arraylen;i++)
    {
        cout<< "UPC " << i << ": " << UPC[i] << "\t" << "Phrase " << i << ": " << phrase[i] << endl;

    }*/

    return 0;
}
