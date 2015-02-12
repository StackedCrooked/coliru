#include <iostream>
#include <strings.h>

using namespace std;

string Coder(string phrase,int K)
{
    for(size_t i=0;i<phrase.size();i++)
    {
        if(phrase[i]>'A'&& phrase[i]<'Z')
        {
            if(phrase[i]+K>'Z')
            {
                phrase[i]=phrase[i]+K-26;
            }
            if(phrase[i]+K<'A')
            {
                phrase[i]=phrase[i]+K+26;
            }
        }//Maj case

        if(phrase[i]>'a'&& phrase[i]<'z')
        {
            if(phrase[i]+K>'z')
            {
                phrase[i]=phrase[i]+K-26;
            }
            if(phrase[i]+K<'a')
            {
                phrase[i]=phrase[i]+K+26;
            }
        }//Min case

        if(phrase[i]>'0' && phrase[i]<'9')
        {
            if(phrase[i]+K>'9')
            {
                phrase[i]=phrase[i]+K-10;
            }
            if(phrase[i]+K<'0')
            {
                phrase[i]=phrase[i]+K+10;
            }//number case
            //no change for weird carac not deleted
        }
    }
    cout<<phrase<<endl;
    return phrase;

int main()
{
    return 0;
}
