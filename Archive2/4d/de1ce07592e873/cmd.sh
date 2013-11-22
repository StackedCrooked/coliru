#include<iostream>
#include<conio.h>
#include<vector>

using namespace std;

class ElementPile
{
private:
	int val;
public:
	ElementPile(int val)
	{
		this->val = val;
	}
	void Set(int a)
	{
		val = a;
	}
	int get()
	{
		return val;
	}
};

class Pile
{
private:
	int taille;
	vector<ElementPile>Tab;
public:
	Pile()
	{
		taille = 0;
		
	}
	bool EstVide()
	{
		if (taille==0)
			return true;
		else
			return false;
	}

	void Empiler(int x)
	{
	    ElementPile N(x);
		if (taille < sizeof(Tab))
		{
			taille++;
			Tab.push_back(N);

		}
		else
		{
			vector<ElementPile>T;
			for (int i(0) ; i<sizeof(Tab) ; ++i)
			{
				T.push_back(Tab[i].get());
			}
			T.push_back(N);
			taille++;
			Tab = T;
		}
		cout <<endl ;
	}

	void Afficher()
	{
		cout <<endl <<"La pile est constituee de: ";
		for (int i(0) ; i<taille ; i++)
		{
			cout<<Tab[i].get() <<" . " ;
		}
		cout <<endl;
	}

	void Depiler()
	{
		cout<<"Le sommet qu'on va enlever est: " <<Tab[taille-1].get() <<endl;
		taille--;
		Tab.pop_back();
		
	}

	int Sommet()
	{
		return Tab[taille-1].get() ; 
	}
};



void main()
{
    Pile *P=new Pile();
	int x;
	int c;
	cout<<"Les choix possibles sont :" <<endl <<"1- Empiler la pile" <<endl <<"2- Depiler la pile" <<endl 
		<<"3- Verifier si la pile est vide ou pas" <<endl <<"4- Afficher le sommet de la pile" <<endl
		<<"5- Afficher la pile" <<endl <<"6- Fermer cette application." <<endl <<"Faites votre choix:" <<endl ;
	do
	{
	cout <<endl <<"    *************************   " <<endl <<" Vous avez choisi: ";
	cin >>c;
	cout <<endl;
	switch (c)
	{
	case 1: 
		cout<<"Donnez l'element a ajouter a la pile: ";
		cin >>x;
		P->Empiler(x);
		P->Afficher();
		break;
	case 2:
		P->Depiler();
		P->Afficher();
		break;
	case 3:
		cout <<"La Pile est-elle vide? (1:oui et 0:non) "<<endl 
			<<"La reponse est : " <<P->EstVide()<<endl;
		break;
	case 4:
		cout <<endl <<"Le sommet de la pile a cet instant est : "
			<<P->Sommet()<<endl;
		break;
	case 5:
		P->Afficher();
		break;
	case 6:
		cout <<"A la prochaine fois ;)";
		break;
	default:
		cout <<"Le nombre choisi ne fait pas partie des choix mis a votre disposition!"
			<<endl <<"Merci de bien vouloir choisir un nouveau nombre " <<endl;
	}