//#include "stdafx.h"
#include <iostream>
#include <string>
#include <math.h>
//CPE Spé C groupe TIPE N°17
using namespace std;

string KeyToMaj(string key)
{
    for (size_t i=0; i<key.length(); ++i)
    {
        key[i] = toupper(key[i]);
    }
    return key;
}

string Effacer(string phrase)
{
    for (size_t i = 0; i<phrase.length(); i++)
	{
		char c = phrase[i];
		if (c == -126 || c == -118 || c == -119 || c == -120)
			phrase[i] = 'e';
		else if (c == -125 || c == -124 || c == -123 || c == -122 || c == -96)
			phrase[i] = 'a';
		else if (c == -117 || c == -116 || c == -115 || c == -95)
			phrase[i] = 'i';
		else if (c == -109 || c == -108 || c == -107 || c == -94)
			phrase[i] = 'o';
		else if (c == -127 || c == -106 || c == -105 || c == -93)
			phrase[i] = 'u';
		else if (c == -104)
			phrase[i] = 'y';
		else if (c == -121)
			phrase[i] = 'c';
		else if (c == -92)
			phrase[i] = 'n';
		else if (c == -114 || c == -113)
			phrase[i] = 'A';
		else if (c == -112)
			phrase[i] = 'E';
		else if (c == -103)
			phrase[i] = 'O';
		else if (c == -102)
			phrase[i] = 'U';
		else if (c == -91)
			phrase[i] = 'N';
		else if (c == -111)
			phrase.replace(i, 1, "ae");
		else if (c == -110)
			phrase.replace(i, 1, "AE");

	}
	return phrase;
}

void euclideEtendu(int a, int b, int &u, int &v)
{
	int x(1), xx(0);
	int y(0), yy(1);
	int q(0);
	int var(0);

	while (b != 0)
	{
		q = a / b;
		var = a;
		a = b;
		b = var%b;
		var = xx;
		xx = x - q*xx;
		x = var;
		var = yy;
		yy = y - q*yy;
		y = var;
	}
	u = x;
	v = y;
	cout << u << endl << v << endl;

}

void Cle(int *T)
{
	//choix de la cle
	int p, q, n, e, phi, clePrive,a(0),b(0);
	cout << "Entrer le premier nombre premier p" << endl;
	cin >> p;
	cout << "Entrer le deuxieme nombre premier q" << endl;
	cin >> q;
	n = p*q;
	phi = (p - 1)*(q - 1);
	cout << a << endl;
	cout << "n=p*q=" << n << endl << "phi(n)=" << phi << endl;
	cout << "Entrer l'exposant" << endl;
	cout<<"phi"<<phi<<endl;
	do
    {
        cin >> e;
    }while (e>=phi);
	euclideEtendu(e, phi, a, b);
	cout << "inverse d de e : " << a << endl;
	do
    {
        a=a+phi;
    }while(a<0);
	clePrive = (a)%phi;
	cout << "La clef priv" << "\x82" << "e est :(" << n << "; " << clePrive << ")" << endl << "La clef publique est : (" << n << "; " << e << ")" << endl;
	T[0] = n;
	T[1] = e;
	T[2] = clePrive;

}

string Message()
{
	cout << "Entrer le message a Decry/crypter" << endl;
	string phrase;
	//cin.ignore();
	getline(cin, phrase);
	phrase = Effacer(phrase);
	phrase=KeyToMaj(phrase);
	cout << phrase << endl;
	return phrase;
}

long double Try(long double c, int *T)
{
    double i;
    long double b;
    do
    {
        i=6;
        b=powl(10.0,i);
        do
        {
            i=i+1;
            b=powl(10.0,i);
        }while(c>=b);
        i=i-1;
        do
        {
            c=c-powl(10,i-3)*T[0];
        }while(c>=powl(10,i));
        cout<<" b "<<" c "<<c<<endl;
    }while(c>=pow(10,6));
    return c;
}

string chiffrement(string phrase, int *T, long double *T1)
{
	for (int i = 0; i<phrase.length(); i++)
	{
	    long double c;
	    c=powl((int)phrase[i],T[1]);
	    cout<<c<<endl;
        T1[i]=fmodl(c,T[0]);
        cout<<"chiffré est"<<T1[i]<<endl;
	}
	return phrase;
}

string chiffrB(string phrase, int *T)
{
    cout<<T[0]<<T[1]<<endl;
    for (int i = 0; i<phrase.length(); i++)
    {
        if(phrase[i]!=32)
        {
            long double c;
            c=phrase[i]-'A';
            cout<<c<<endl;
            c=powl(c,T[1]);

            cout<<c<<endl;

            c=Try(c, T);

            cout<<c<<endl;
            c=fmodl(c,T[0]);
            phrase[i]=c;
            cout<<c<<endl;
        }
    }
    return phrase;
}

string dechif(string phrase, int *T, long double *T1)
{
    for(int i=0;i<phrase.length();i++)
    {
        cout<<T[0]<<" c "<<T[2]<<" b "<<endl;
        cout<<T1[i]<<" 1 "<<endl;
        long double c;
        c=powl(T1[i],T[2]);
        T1[i]=fmodl(c,T[0]);
        cout<<T1[i]<<endl;
        phrase[i]=T1[i];
        cout<<phrase[i]<<" c"<<endl;

    }
    return phrase;
}


string dechifB(string phrase, int *T)
{
    for (int i = 0; i<phrase.length(); i++)
    {
        if(phrase[i]!=32)
        {
            long double c;
            cout<<(int)phrase[i]<<endl;
            c=phrase[i];
            c=powl(c,T[2]);
            cout<<c<<endl;
            c=fmodl(c,T[0]);
            phrase[i]=c+'A';
            cout<<c<<endl;
        }
    }
    return phrase;
}

int main()
{
	int T[3];
	long double T1[1000];
	string phrase;
    //phrase=Message();
    phrase="HELLO";
	Cle(T);
	//phrase=chiffrement(phrase, T, T1);
	phrase=chiffrB(phrase,T);
	cout<<phrase;

    phrase=dechifB(phrase, T);
	//phrase=dechif(phrase, T, T1);
	cout<<phrase;

	return 0;
}
