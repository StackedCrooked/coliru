#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <array>
using namespace std;

const unsigned int DIM(10);

bool remplitGrille(array<array<bool, DIM>, DIM>& grille,
    			   unsigned int ligne, unsigned int colonne,
                   char direction, unsigned int longueur);

void demanderPosition(int limite, array<array<bool, DIM>, DIM>& grille);

void afficherGrille(array<array<bool, DIM>, DIM>& grille);

int main () {

	array<array<bool, DIM>, DIM> grille;
	
	for (auto& element : grille) {
		for (auto& truc : element) {
			truc = false;
		}
	}
	
	demanderPosition(3, grille);
	return 0;
}

bool remplitGrille(array<array<bool, DIM>, DIM>& grille,
				   unsigned int ligne, unsigned int colonne,
                   char direction, unsigned int longueur)
{
	bool rempli(true);
	
	unsigned int i(ligne), j(colonne);
	bool varie_j, varie_i;
	
	switch (direction) {
		case 'N':
			i = colonne - longueur;
			varie_i = true;
			varie_j = false;
			break;
		case 'S':
			varie_i = true;
			varie_j = false;
			break;
		case 'E':
			varie_i = false;
			varie_j = true;
			break;
		case 'O':
			j = ligne - longueur;
			varie_i = false;
			varie_j = true;
			break;
		default:
			varie_i = false;
			varie_j = true;
			break;
	}
	
	unsigned int k, l;
	if (varie_i) { k = i; for (l = k; l < longueur; l++) { if (grille[l][j] == true) { rempli = false; } } }
	if (varie_j) { k = j; for (l = k; l < longueur; l++) { if (grille[i][l] == true) { rempli = false; } } }
	
	if (rempli) {
		for (;k < longueur; k++) {
			if (varie_i) { grille[k][j] = true; }
			else { grille[i][k] = true; }
		}
	}
	
	return rempli;
}
				  
void demanderPosition(int limite, array<array<bool, DIM>, DIM>& grille) {
	for (int i(0); i < limite; i++) {
		unsigned int x, y, taille;
		char dir;
		cout << "Entrez coordonnée x : "; cin >> x;
		cout << endl << "Entrez coordonnée y : "; cin >> y;
		cout << endl << "Entrez direction (N,S,E,O) : "; cin >> dir;
		cout << endl << "Entrez taille : "; cin >> taille;
		cout << endl << "Placement en (" << x << "," << y <<
						") direction " << dir << 
						" longueur " << taille <<
						" : ";
		if (remplitGrille(grille, x-1, y-1, dir, taille))
			cout << "SUCCES";
		else 
			cout << "ECHEC";

		cout << endl;
	}
	afficherGrille(grille);
}

void afficherGrille(array<array<bool, DIM>, DIM>& grille) {
	cout << endl << "Voilà la grille de jeu : " << endl;
	for (unsigned int i(0); i < DIM; i++) {
		for (unsigned int j(0); j < DIM; j++) {
			if (grille[i][j])
				cout << "#";
			else 
				cout << ".";
		}
		cout << endl;
	}
}
