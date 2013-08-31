#include <iostream>
using namespace std;

int main()
{
int reponse;
  do
  {
  cout << "Mathilde est-elle une pute? 1 pour oui, 2 pour non" <<endl;
  cin>>reponse;
  
  if (reponse==1)
  {
    cout<<"en effet" << endl;
  }
  if (reponse== 2)
  {
    cout << "votre reponse est invalide vous faites erreur, veuillez repondre a nouveau:"<< endl;
  }
  }while (reponse==2);
    
   return 0;
}

