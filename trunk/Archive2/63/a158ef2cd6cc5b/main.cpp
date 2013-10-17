#include <iostream>
using namespace std;

int main()
{
  cout << "Pensez a un personnage : Mlle Rose, le Professeur Violet, "
       << "le Colonel Moutarde," << endl
       << "le Reverend Olive ou Mme Leblanc." << endl << endl;

  cout << "Votre personnage a-t-il des moustaches (1 : oui, 0 : non) ? ";
  bool moustaches;
  cin >> moustaches;

  cout << "Votre personnage porte-t-il des lunettes ? ";
  bool lunettes;
  cin >> lunettes;

  cout << "Votre personnage porte-t-il un chapeau ? ";
  bool chapeau;
  cin >> chapeau;

  cout << "Est-ce que votre personnage est un homme ? ";
  bool homme;
  cin >> homme;

  cout << "==> Le personnage auquel vous pensez est ";

  if (chapeau) {
    /*******************************************
     * Completez le programme a partir d'ici.
     *******************************************/
   cout << "le Professeur Violet";
  } else {
      if (moustaches) {
        cout << "le Colonel Moutarde";
      } else {
         if (homme) {
           cout << "le Reverend Olive";
         } else {
            if (lunettes) {
              cout << "Mme Leblanc";
            } else {
                cout << "Mlle Rose";
            }
         }
      }
  
   
    /*******************************************
     * Ne rien modifier apres cette ligne.
     *******************************************/
  }

  cout << endl;

  return 0;
}
