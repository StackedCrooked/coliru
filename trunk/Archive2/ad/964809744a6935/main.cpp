// Compilation avec GCC-4.8 ou plus: g++ -std=c++11 frequences.cpp
// Compilation avec Clang 3.4 ou plus: clang++ -std=c++11 frequences.cpp
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <cassert>

typedef std::vector<std::tuple<int,int>> Tableau2D;

Tableau2D calculer_frequences(Tableau2D const& tab)
{
    std::map<int, int> tmp;
    for(auto& ligne: tab)
	{
		int const& c= std::get<0>(ligne);
		int const& freq= std::get<1>(ligne);
		assert(freq>0);
		tmp[c]+= freq;
	}
	std::vector<std::tuple<int,int>> ret_value;
	for(auto& element: tmp)
	{
		ret_value.push_back(std::make_tuple(element.first,element.second));
	}

	return std::move(ret_value);
}

void afficher_frequences(Tableau2D const& tab)
{
    std::cout<<"------------"<<std::endl;
	std::cout<<"Affichage de "<< &tab<<std::endl;
	for(auto& ligne: tab)
	{
		int const& c= std::get<0>(ligne);
		int const& freq= std::get<1>(ligne);
		std::cout<< c << " -> "<< freq<<std::endl;
	}
	std::cout<<"Fin de l'affichage "<<&tab<<std::endl;
    std::cout<<"------------"<<std::endl;
}

// d'un tableau 2D style C vers un tableau type C++
Tableau2D tableauC_vers_Cpp(int* tab,int* freq, int n)
{
	Tableau2D ret_value;
	assert(tab!=NULL);
	assert(freq!=NULL);
	for(int itr=0;itr<n;++itr)
	{
		ret_value.push_back(std::make_tuple(tab[itr],freq[itr]));
	}
	return std::move(ret_value);
}

int main()
{
	int tabC[2][6]={{1, 1, 3, 85, 2, 1},{2,1,2,6,3,5}};

	Tableau2D tab=tableauC_vers_Cpp(tabC[0],tabC[1],6); // transformer cela en un tableau style C++
	afficher_frequences(tab);
	std::cout<<"calcul de frequences"<<std::endl;
	tab=calculer_frequences(tab); // le tableau est maintenant trié selon la première colonne et la deuxième contient la frequence totale
	afficher_frequences(tab);
	return 0;
}
