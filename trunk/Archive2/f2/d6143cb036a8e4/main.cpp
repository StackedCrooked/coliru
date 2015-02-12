#include <iostream>
#include <strings.h>

using namespace std;

string MessageACryprer()
{
    cout<<"Entrer le message a cryper d'après le codage de césar"<<endl;
    string phrase;
    getline(cin, phrase);
    return phrase;
}

string Eraseshits(string phrase)
{
    size_t ph;
    do
    {
        if(ph!=std::string::npos)
        {
            ph=phrase.find_first_of(" ,./!()=+-_:?;'");
            phrase.erase(phrase.begin()+ph);
            cout<<phrase<<endl;
        }
    }while(ph!=std::string::npos);
    cout<<phrase;
    return phrase;
}
int main()
{
    string Phrase;
    Phrase="Blabla, zrgu; a/(). azurh";
    Phrase=Eraseshits(Phrase);
    return 0;
}
