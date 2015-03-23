#include "stdafx.h" //A utiliser dans certain cas (ordi de la prépa)
#include <iostream>
#include <string>
#include <math.h>
//CPE Spé C groupe TIPE N°17
using namespace std;

int premier(int P)
{
    int j;
    j = sqrt(P);
    for (int i = 2; i <= j; i++)
    {
        if (P % i == 0)
            return 0;
    }
    return 1;
}

int PremierEntreEux(int a, int b)
{
    int z=0;
    do
    {
        z = a % b;
        if(z == 0)
        {
            z = b;
            break;
        }
        a = b;
        b = z;
    }while(b!=0 || z!=1);
    return z;
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
}

void Cle(int *T)
{
	//choix de la cle
	int p, q, n, e, phi, clePrive,a(0),b(0),z;
	cout << "Entrer le premier nombre premier p" << endl;
	do
    {
        cin >> p;
        z=premier(p);
    }while(z==0);
	cout << "Entrer le deuxieme nombre premier q" << endl;
	do
    {
        cin >> q;
        z=premier(q);
    }while(z==0 && q!=p);
	n = p*q;
	phi = (p - 1)*(q - 1);
	cout << "n=p*q=" << n << endl << "phi(n)=" << phi << endl;
	cout << "Entrer l'exposant" << endl;
	z=0;
	do
    {
        cin >> e;
        z=PremierEntreEux(e,phi);
    }while (e>=phi || z!=1);
	euclideEtendu(e, phi, a, b);
	cout << "inverse d de e : " << a << endl;
	do
    {
        a=a+phi;
    }while(a<0);
	clePrive = (a)%phi;
	cout << endl << "La clef publique est : (" << n << "; " << e << ")" << "La clef priv" << "\x82" << "e est :(" << n << "; " << clePrive << ")" << endl;
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
	return phrase;
}


string chiffrement(string phrase, int *T, long double *T1)
{
	for (int i = 0; i<phrase.length(); i++)
	{
	    long int c;
	    c=1;
	    for(int j=0; j<T[1];j++)
        {
            c=c*phrase[i];
            c=c%T[0];
        }
	    phrase[i]=c;
	    T1[i]=c;
	}
	return phrase;
}


string dechif(string phrase, int *T, long double *T1)
{
    for(int i=0;i<phrase.length();i++)
    {
        long int c;
	    c=1;
        for(int j=0; j<T[2];j++)
        {
            c=c*T1[i];
            c=c%T[0];
        }

        phrase[i]=c;

    }
    return phrase;
}


int main()
{
	int T[3];
	long double T1[1000];
	string phrase;
    phrase=Message();
	Cle(T);
	phrase=chiffrement(phrase, T, T1);
	cout<<phrase<<endl;
	phrase=dechif(phrase, T, T1);
	cout<<phrase;

	return 0;
}
