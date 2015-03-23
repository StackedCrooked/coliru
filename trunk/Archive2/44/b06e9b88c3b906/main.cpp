//#include "stdafx.h" A utiliser sur Visual Studio
#include <iostream>
#include <string>
//CPE Spé C groupe TIPE N°17
using namespace std;

string Message()
{
    cout<<"Entrer le message a Decry/crypter d'apres le codage de César"<<endl;
    string phrase;
    cin.ignore();
    getline(cin, phrase);
    return phrase;
}

int Key()
{
    int K;
    cout<<"Entrer la cle"<<endl;
    cin>>K;
    K = K % 26;
    if(K<0)
    {
        do
        {
            K=K+26;
        }while(K<0);
    }
    return K;
}

string Effacer(string phrase)
{
    int ph;
    do
    {
        ph=phrase.find_first_of(" , ./^%*µ$€°~#|`!\()=+-_:?;'<>&[]{}"); //delete every weird character
        if(ph!=-1) // or std::string::npos
        {
            phrase.erase(phrase.begin()+ph);
        }
    }while(ph!=-1); // or std::string::npos

    for(size_t i=0;i<phrase.length();i++)
    {
        char c=phrase[i];
        if(c==-126||c==-118||c==-119||c==-120)
            phrase[i]='e';
        else if(c==-125||c==-124||c==-123||c==-122||c==-96)
            phrase[i]='a';
        else if(c==-117||c==-116||c==-115||c==-95)
            phrase[i]='i';
        else if(c==-109||c==-108||c==-107||c==-94)
            phrase[i]='o';
        else if(c==-127||c==-106||c==-105||c==-93)
            phrase[i]='u';
        else if(c==-104)
            phrase[i]='y';
        else if(c==-121)
            phrase[i]='c';
        else if(c==-92)
            phrase[i]='n';
        else if(c==-114||c==-113)
            phrase[i]='A';
        else if(c==-112)
            phrase[i]='E';
        else if(c==-103)
            phrase[i]='O';
        else if(c==-102)
            phrase[i]='U';
        else if(c==-91)
            phrase[i]='N';
        else if(c==-111)
            phrase.replace(i,1,"ae");
        else if(c==-110)
            phrase.replace(i,1,"AE");
    }

    cout<<phrase<<endl;
    return phrase;
}

string Cipher(string phrase,int K)
{
    for(size_t i=0;i<phrase.length();i++)
    {
        if(phrase[i]>='A' && phrase[i]<='Z')
        {
            phrase[i]='A'+((phrase[i]-'A'+K)%26);
        }//Maj case

        else if(phrase[i]>='a' && phrase[i]<='z')
        {
            phrase[i]='a'+((phrase[i]-'a'+K)%26);
        }//Min case

        else if(phrase[i]>='0' && phrase[i]<='9')
        {
            phrase[i]='0'+((phrase[i]-'0'+K)%10);
        }
    }
    cout<<phrase<<endl;
    return phrase;
}

int main()
{
    string Phrase;
    int a;
    int cle;
    cout<<"Cripter : 1"<<endl<<"Decripter : 2"<<endl;
    cin>>a;
    if(a==1)
    {
    Phrase=Message();
    cle=Key();
    Phrase=Effacer(Phrase);
    Phrase=Cipher(Phrase,cle);
    }
    if(a==2)
    {
    Phrase=Message();
    cle=Key();
    Phrase=Cipher(Phrase,cle);
    }

    return 0;
}
