// header

#include <string.h>
#include <map>

using namespace std;

enum Token { INVALID = 0, lANGLE=1, rANGLE=2,iD=3, eQ=4, sLASH=5, qSTRING=6, oTHER=7, eND=8, tEXT=9};

map <Token, int> counter;

extern Token getToken(istream *br, string& lexeme);


// token.cpp

//#include "suffix.h"
#include <iostream>
#include <fstream>
#include <map>
#include <cctype>

bool slash = false;
bool text = false;
bool quote = false;
bool id = false;
bool equ =  false;
bool other = false;
bool qstring = false;
char prev=NULL;

Token getToken(istream *in, string& lexeme)
{
    char c;
    char prev;
    lexeme="";

    int intSlash = 0;

    int intText = 0;

    int intQuote = 0;

    int intId = 0;

    int intEqual = 0;

    int intOther = 0;

    int intQstring = 0;

    int langlec = 0;
    int  intLangle = 0;

    int ranglec = 0;
    int  intRangle = 0;

    if (in->eof())
        return eND;

    while (in->get(c))
    {
        switch (c)
        {
            case '/' :
                if (quote == false && langlec > 0)
                {
                    slash = true;
                    intSlash++;
                    return sLASH;
                }
                break;

            case '=' :
                if (quote == false && langlec > 0)
                {
                    equ = true;
                    intEqual++;
                    return eQ;
                }
                break;

            case '<' :

                if (  prev != ' '  && langlec == 0)
                {intText++ ;
                    return tEXT;}

                if (quote == false)
                {
                    langlec ++;
                    intLangle ++;
                    id = true;
                    return lANGLE;
                }


                break;


            case '>' :

                if (quote != true)
                {
                    ranglec++;
                    intRangle++;
                    return rANGLE;

                    if (langlec > 0)
                    {
                        langlec--;
                        id = false;
                    }
                }
                break;

            case '"' :
                if (langlec > 0 && quote == true)
                {
                    quote = false;
                    id = true;
                    intQstring ++;
                    intOther--;
                    return qSTRING;
                }
                else if (langlec > 0)
                {
                    intOther++;
                    quote = true;
                    return oTHER;
                }



                break;

            case ' ':
                if ( prev != ' ' && prev != '<' && prev != '>' && quote == false){
                    if (langlec == 0){
                        intText++;
                        return tEXT;
                    }
                }
                else if ( prev != '/' && prev != '=')
                {intId++;
                    return iD;
                }

                break;

            default:

                if (quote == true)
                {
                    id = false;
                }

                else if (id==true)
                {
                    intId++;
                    id=false;
                    return iD;
                }
                prev=c;

        }
    }
    return INVALID;
}


// main.cpp

#include <iostream>
#include <fstream>
#include <map>
#include <cctype>
#include <string>
#include <algorithm>
//#include "suffix.h"

using namespace std;

    int
main( int argc, char *argv[] )
{
    istream *br;
    ifstream infile;
    // check args and open the file
    if( argc == 1 )


        br = &cin;
    else if( argc != 2 ) {
        cout<<"THERE IS A FATAL ERROR"<<endl;
        return 1; // print an error msg
    } else {
        infile.open(argv[1]);
        if( infile.is_open() )
            br = &infile;
        else {
            cout << argv[1] << " can't be opened" << endl;
            return 1;

        }
    }
    string tokens="";
    Token typeOfToken;

    while(true){
        typeOfToken=getToken(br,tokens);
        if (counter.count(typeOfToken))
            counter[typeOfToken]+=1;
        else
            counter[typeOfToken]=1;

        if(typeOfToken==8)
            break;
    }
    cout<<"total token count: "<<endl;
    if (counter[lANGLE]!=0)
        cout<<"LANGLE: "<<counter[lANGLE]<<endl;
    if (counter[rANGLE]!=0)
        cout<<"RANGLE: "<<counter[rANGLE]<<endl;
    if (counter[tEXT]!=0)
        cout<<"TEXT: "<<counter[tEXT]<<endl;
    if (counter[iD]!=0)
        cout<<"ID: "<<counter[iD]<<endl;
    if (counter[eQ]!=0)
        cout<<"EQ: "<<counter[eQ]<<endl;
    if (counter[sLASH]!=0)
        cout<<"SLASH: "<<counter[sLASH]<<endl;
    if (counter[qSTRING]!=0)
        cout<<"QSTRING: "<<counter[qSTRING]<<endl;
    if (counter[oTHER]!=0)
        cout<<"OTHER: "<<counter[oTHER]<<endl;

    return 0;
}
