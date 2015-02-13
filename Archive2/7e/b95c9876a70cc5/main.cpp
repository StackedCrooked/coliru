#include <iostream>
#include <string>

using namespace std;

string Message()
{
    cout<<"Entrer le message a Decri/criper d'après le codage de césar"<<endl;
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
    return K;
}

string Eraseshits(string phrase)
{
    size_t ph;
    do
    {
        ph=phrase.find_first_of(" ,./^%*µ$€°~#|`!\()=+-_:?;'<>&[]{}"); //delete every weird character
        if(ph!=std::string::npos) // or -1
        {
            phrase.erase(phrase.begin()+ph);
        }
    }while(ph!=std::string::npos); // or -1
    cout<<phrase<<endl;
    return phrase;
}

string Chiper(string phrase,int K)
{
    K = K % 26;
    for(size_t i=0;i<phrase.length();i++)
    {
        if(phrase[i]>='A'&& phrase[i]<='Z')
        {
            phrase[i]=phrase[i]+K;
            if(phrase[i]>'Z')
            {
                phrase[i]=phrase[i]-26;
            }
            if(phrase[i]<'A')
            {
                phrase[i]=phrase[i]+26;
            }
        }//Maj case

        if(phrase[i]>='a'&& phrase[i]<='z')
        {
            phrase[i]=phrase[i]+K;
            if(phrase[i]>'z')
            {
                phrase[i]=phrase[i]-26;
            }
            if(phrase[i]<'a')
            {
                phrase[i]=phrase[i]+26;
            }
        }//Min case

        if(phrase[i]>='0' && phrase[i]<='9')
        {
            phrase[i]=phrase[i]+K;
            if(phrase[i]>'9')
            {
                phrase[i]=phrase[i]-10;
            }
            if(phrase[i]<'0')
            {
                phrase[i]=phrase[i]+10;
            }//number case
            //no change for weird carac not deleted
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
    cout<<"Chiper : 1"<<endl<<"Dechiper : 2"<<endl;
    cin>>a;
    if(a==1)
    {
    Phrase=Message();
    cle=Key();
    Phrase=Eraseshits(Phrase);
    Phrase=Chiper(Phrase,cle);
    }
    if(a==2)
    {
    Phrase=Message();
    cle=Key();
    Phrase=Chiper(Phrase,cle);
    }

    return 0;
}
