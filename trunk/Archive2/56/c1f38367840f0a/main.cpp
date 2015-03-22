#include <iostream>
#include <string>
//CPE Spé C groupe TIPE N°17
using namespace std;

string Effacer(string phrase)
{
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
    return phrase;
}

string KeyToMaj(string key)
{
    key=Effacer(key);
    for (size_t i=0; i<key.length(); ++i)
    {
        key[i] = toupper(key[i]);
    }
    return key;
}


string Message()
{
    cout<<"Entrer le message a Decry/crypter d'aprés le codage de Vigenère"<<endl;
    string phrase;
    //cin.ignore();
    getline(cin, phrase);
    phrase=Effacer(phrase);
    cout<<phrase<<endl;
    return phrase;
}

string Key()
{
    cout<<"Entrer la clé"<<endl;
    string key;
    //cin.ignore();
    getline(cin, key);
    key=KeyToMaj(key);
    cout<<key<<endl;
    return key;
}


string vigenereC(string phrase, string key, int b, int ph, int y)
{
    for(int i=0; i<ph; i++)
    {
        int c;
        c=i+b-y;
        c=c%key.length();
        if(phrase[b+i]>='A' && phrase[b+i]<='Z')
        {
            phrase[b+i]='A'+((phrase[b+i]-'A'+key[c]-'A')%26);
        }

        else if(phrase[b+i]>='a' && phrase[b+i]<='z')
        {
            phrase[b+i]='a'+((phrase[b+i]-'a'+key[c]-'A')%26);
        }

        else if(phrase[b+i]>='0' && phrase[b+i]<='9')
        {
            phrase[b+i]='0'+((phrase[b+i]-'0'+key[c])%10);
        }
    }
    return phrase;
}

string vigenereD(string phrase, string key, int b, int ph, int y)
{
    for(int i=0; i<ph; i++)
    {
        int c;
        c=i+b-y;
        c=c%key.length();
        if(phrase[b+i]>='A' && phrase[b+i]<='Z')
        {
            phrase[b+i]=phrase[b+i]-key[c];
            do
            {
                phrase[b+i]=phrase[b+i]+26;
            }while(phrase[b+i]<0);
            phrase[b+i]=phrase[b+i]%26;
            phrase[b+i]=phrase[b+i]+'A';
        }

        else if(phrase[b+i]>='a' && phrase[b+i]<='z')
        {
            phrase[b+i]=phrase[b+i]-'a'-(key[c]-'A');
            do
            {
                phrase[b+i]=phrase[b+i]+26;
            }while(phrase[b+i]<0);
            phrase[b+i]=phrase[b+i]%26;
            phrase[b+i]=phrase[b+i]+'a';
        }
        else if(phrase[b+i]>='0' && phrase[b+i]<='9')
        {
            phrase[b+i]=phrase[b+i]-'0'-(key[c]-'A');
            do
            {
                phrase[b+i]=phrase[b+i]+10;
            }while(phrase[b+i]<0);
            phrase[b+i]=phrase[b+i]%10;
            phrase[b+i]=phrase[b+i]+'0';
        }
    }
    return phrase;
}


string VigeB(string phrase, string key, int m)
{
    int b,y,ph;
    ph=phrase.find_first_of(" , ./^%*µ$€°~#|`!\()=+-_:?;'<>&[]{}");
    b=0;
    y=0;
    string phraseb;
    phraseb=phrase;
    do
    {
        ph=phraseb.find_first_of(" , ./^%*µ$€°~#|`!\()=+-_:?;'<>&[]{}");
        if(m==1)
        {
            phrase=vigenereC(phrase, key, b, ph, y);
        }
        if(m==2)
        {
            phrase=vigenereD(phrase, key, b, ph, y);
        }
        phraseb=phraseb.erase(0, ph+1);
        b=ph+b+1;
        y=y+1;
    }while(ph!=-1);
    if(m==1)
    {
        phrase=vigenereC(phrase, key, b, phraseb.length(), y-1);
    }
    if(m==2)
    {
        phrase=vigenereD(phrase, key, b, phraseb.length(), y-1);
    }
    cout<<phrase<<endl;

    return phrase;
}


int main()
{
    string phrase;
    string key;
    phrase=Message();
    key=Key();

    phrase=VigeB(phrase, key, 1);

    phrase=VigeB(phrase, key, 2);
    return 0;
}