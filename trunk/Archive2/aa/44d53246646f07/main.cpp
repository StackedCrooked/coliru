#include <iostream>
#include <math.h>



using namespace std;

int choix_principal()
{
    cout << "-------------------------------------------------------------------------------"<<endl;
    cout << "|                                                                             |"<<endl;
    cout << "|                       Programme pour les suites                             |"<<endl;
    cout << "|                                                                             |"<<endl;
    cout << "-------------------------------------------------------------------------------\n\n\n\n\n"<<endl;
    cout << "  Quel type de suite souhaitez-vous etudier ? (Tapez le numero correspondant)"<<endl<<endl<<endl;
    cout << "1) Suite arithmetique"<<endl;
    cout << "2) Suite geometrique"<<endl<<endl<<endl;
    int x;
    do
    {
        cout << "Votre choix : ";
        cin >> x;
    }while (x!=1 && x!=2);
    cout <<endl<<endl<<endl<<endl;
    return x;

}

int choix_de_letudeFONCT()
{
    cout << "            Que souhaitez-vous etudier par rapport a cette suite ?"<<endl;
    cout << "                      (Tapez le numero correspondant)       "<<endl;
    cout << "          (Le sens de variation sera donne quelque soit votre choix)             "<<endl<<endl<<endl;
    cout << "1) Un terme bien precis"<<endl;
    cout << "2) Toutes les valeurs comprises entre un terme et un autre"<<endl<<endl<<endl;
    int x;
    do
    {
        cout << "Votre choix : ";
        cin >> x;
    }while (x!=1 && x!=2);
    cout <<endl<<endl<<endl<<endl;
    return x;
}

int valeur_indice_premier_termeFONCT()
{
    cout << "      Quelle est la valeur de l'indice du premier terme de la suite ?"<<endl<<endl<<endl;
    int x;
    do
    {
        cout << "Valeur de l'indice du premier terme de la suite : ";
        cin >> x;
    } while (x<0);
    cout <<endl<<endl<<endl<<endl;
    return x;
}

int information_sur_la_suiteFONCT()
{
    cout << "                     Que connait-on sur cette suite ?" <<endl;
    cout << "                      (Tapez le numero correspondant)       "<<endl<<endl<<endl;
    cout << "1) La valeur de deux termes ainsi que leurs indices correspondants"<<endl;
    cout << "2) La valeur d'un terme et de la raison de cette suite"<<endl<<endl<<endl;
    int x;
    do
    {
        cout << "Votre choix : ";
        cin >> x;
    }while (x!=1 && x!=2);
    cout <<endl<<endl<<endl<<endl;
    return x;

}
double recup_terme ()
{
    cout << "                   Quelle est la valeur d'un des termes ?" << endl<<endl<<endl;
    cout << "Valeur du terme : ";
    double x;
    cin >> x;;
    cout <<endl<<endl<<endl<<endl;
    return x;
}

int recup_indice (int valeur_indice_premier_terme)
{
    cout << "         Quelle est la valeur de l'indice correspondant a ce terme ?" <<endl<<endl<<endl;
    int x;
    do
    {
        cout << "Valeur de l'indice de ce terme : ";
        cin >> x;
    } while (x<valeur_indice_premier_terme);
    cout <<endl<<endl<<endl<<endl;
    return x;

}

double recup_raison ()
{
    cout << "               Quelle est la valeur de la raison de cette suite ?" <<endl<<endl<<endl;
    cout << "Valeur de la raison : ";
    double x;
    cin >> x;
    cout <<endl<<endl<<endl<<endl;
    return x;
}

double recup_raison_info1 (int choix_de_la_suite, double terme1, int indice1, double terme2, int indice2, int valeur_indice_premier_terme)
{
    double raison;
    if (choix_de_la_suite==1)
    {
        raison = (terme1-terme2)/(indice1-indice2);
    }
    else
    {
        raison = pow((terme1/terme2), 1.0/(indice1-indice2));
    }
    return raison;
}

double recup_Uo (double raison, double terme1, int indice1, int valeur_indice_premier_terme, int choix_de_la_suite)
{
    double Uo;
    if (choix_de_la_suite==1)
    {
        Uo = terme1 - raison*(indice1-valeur_indice_premier_terme);
    }
    else
    {
        Uo = terme1/pow(raison,indice1-valeur_indice_premier_terme);
    }
    return Uo;
}

void afficher_resultat (int choix_de_letude, int choix_de_la_suite, double Uo, double raison, int valeur_indice_premier_terme)
{
    if (choix_de_letude==1)
    {
        int valeur_indice_terme_voulu;
        cout << "             Quelle est la valeur de l'indice du terme voulu ?"<<endl<<endl<<endl;
        do
        {
            cout << "Valeur de l'indice : ";
            cin >> valeur_indice_terme_voulu;
        }while (valeur_indice_terme_voulu<valeur_indice_premier_terme);
        if (choix_de_la_suite==1)
        {
            double resultat(Uo + (valeur_indice_terme_voulu-valeur_indice_premier_terme)*raison);
            cout << endl << endl << endl << "Le resultat est : " << resultat<<endl;
            if (raison>0)
            {
                cout << "La suite est croissante !"<<endl<<endl;
            }
            else if (raison<0)
            {
                cout << "La suite est decroissante !"<<endl<<endl;
            }
            else
            {
                cout << "La suite est constante"<<endl<<endl;
            }

        }
        else
        {
            double resultat(Uo * pow(raison,valeur_indice_terme_voulu-valeur_indice_premier_terme));
            cout << endl << endl << endl<< "Le resultat est : " << resultat<<endl;
            if (Uo>0 && raison>1)
            {
                cout << "La suite est croissante et tend vers +infini"<<endl<<endl;
            }
            else if (Uo<0 && raison>1)
            {
                cout << "La suite est decroissante et tend vers -infini"<<endl<<endl;
            }
            else if (Uo>0 && raison>0 && raison<1)
            {
                cout << "La suite est decroissante et tend vers 0"<<endl<<endl;
            }
            else if (Uo<0 && raison>0 && raison<1)
            {
                cout << "La suite est croissante et tend vers 0"<<endl<<endl;
            }
            else
            {
                if (raison>-1 && raison<0)
                {
                    cout << "La suite n'a pas de sens de variation mais tend vers 0"<<endl<<endl;
                }
                else
                {
                    cout << "La suite n'a pas de sens de variation et n'a pas de limite"<<endl<<endl;
                }
            }

        }
    }
    else
    {
        int valeur_indice_debut;
        cout << "      Quelle est la valeur de l'indice du premier terme de l'encadrement ?" <<endl<<endl<<endl;
        do
        {
            cout << "Valeur de l'indice : ";
            cin >> valeur_indice_debut;
        }while (valeur_indice_debut<valeur_indice_premier_terme);
        cout << endl<<endl<<endl;
        int valeur_indice_fin;
        cout << "      Quelle est la valeur de l'indice du dernier terme de l'encadrement ?" <<endl<<endl<<endl;
        do
        {
            cout << "Valeur de l'indice : ";
            cin >> valeur_indice_fin;
        }while (valeur_indice_fin<valeur_indice_debut+1);
        if (choix_de_la_suite==1)
        {
            for (int compteur(valeur_indice_debut); compteur<valeur_indice_fin; compteur++)
            {
                if (compteur>9)
                {
                    cout << "U" << compteur << " vaut : " << Uo + (compteur-valeur_indice_premier_terme)*raison << endl;
                }
                else
                {
                    cout << "U" << compteur << "  vaut : " << Uo + (compteur-valeur_indice_premier_terme)*raison << endl;
                }
                if (compteur % 23 ==0)
                {
                    string useless;
                    cout << "Tapez sur une touche puis sur entrer pour continuer !";
                    cin >> useless;
                }
            }
            if (raison>0)
            {
                cout << "La suite est croissante !"<<endl<<endl;
            }
            else if (raison<0)
            {
                cout << "La suite est decroissante !"<<endl<<endl;
            }
            else
            {
                cout << "La suite est constante"<<endl<<endl;
            }
        }
        else
        {
            for (int compteur(valeur_indice_debut); compteur<valeur_indice_fin; compteur++)
            {
                if (compteur>9)
                {
                    cout << "U" << compteur << " vaut : " << Uo*pow(raison,compteur-valeur_indice_premier_terme) << endl;
                }
                else
                {
                    cout << "U" << compteur << "  vaut : " << Uo*pow(raison,compteur-valeur_indice_premier_terme) << endl;
                }
                if (compteur == 23 || compteur == 46 || compteur == 69 || compteur == 92 || compteur == 115 || compteur == 138 || compteur == 161)
                {
                    string useless;
                    cout << "Tapez sur une touche puis sur entrer pour continuer !";
                    cin >> useless;
                }
            }
            if (Uo>0 && raison>1)
            {
                cout << "La suite est croissante et tend vers +infini"<<endl<<endl;
            }
            else if (Uo<0 && raison>1)
            {
                cout << "La suite est decroissante et tend vers -infini"<<endl<<endl;
            }
            else if (Uo>0 && raison>0 && raison<1)
            {
                cout << "La suite est decroissante et tend vers 0"<<endl<<endl;
            }
            else if (Uo<0 && raison>0 && raison<1)
            {
                cout << "La suite est croissante et tend vers 0"<<endl<<endl;
            }
            else
            {
                if (raison>-1 && raison<0)
                {
                    cout << "La suite n'a pas de sens de variation mais tend vers 0"<<endl<<endl;
                }
                else
                {
                    cout << "La suite n'a pas de sens de variation et n'a pas de limite"<<endl<<endl;
                }
            }
        }
    }

}

int main()
{
    int choix_de_la_suite(choix_principal());
    int choix_de_letude(choix_de_letudeFONCT());
    int valeur_indice_premier_terme(valeur_indice_premier_termeFONCT());
    int information_sur_la_suite(information_sur_la_suiteFONCT());
    double terme1 (recup_terme());
    int indice1 (recup_indice(valeur_indice_premier_terme));
    if (information_sur_la_suite==1)
    {
        double terme2 (recup_terme());
        int indice2 (recup_indice(valeur_indice_premier_terme));
        double raison (recup_raison_info1(choix_de_la_suite, terme1, indice1, terme2, indice2, valeur_indice_premier_terme));
        double Uo (recup_Uo(raison, terme1, indice1, valeur_indice_premier_terme, choix_de_la_suite));
        afficher_resultat(choix_de_letude, choix_de_la_suite, Uo, raison, valeur_indice_premier_terme);
    }
    else
    {
        double raison(recup_raison());
        double Uo (recup_Uo(raison, terme1, indice1, valeur_indice_premier_terme, choix_de_la_suite));
        afficher_resultat(choix_de_letude, choix_de_la_suite, Uo, raison, valeur_indice_premier_terme);
    }
    cout << "-------------------------------------------------------------------------------"<<endl;
    cout << "|                              Fin du programme                               |"<<endl;
    cout << "-------------------------------------------------------------------------------"<<endl;
    string useless;
    cout << "Tapez sur une touche puis sur entrer pour continuer !";
    cin >> useless;
    return 0;
}
