#include <iostream>
#include <math.h>
#include <vector>
 
using namespace std;
 
bool estentier(double x)
{
    return x == floor(x);
}
 
void fc_irrationnel(double x, int n, vector<int> & suite_a)
{
    double x1=x;
    int i=0;
    for(i=0;i<n;i++){
        if(x1>0)
            suite_a.push_back(floor(x1));
        x1=1/(x1-floor(x1));
        if(estentier(x1)){
            suite_a.push_back(floor(x1));
            while(i<n)
                i++;
            }   
    }
 
}
 
// calcul l'approximation
double fc_approx(vector<int> &suite_a)
{
    int n = suite_a.size();
    int i = n - 2;
 
    double approx = suite_a[n-1];
 
    while (i>=0)
    {
     
    approx = 1/approx + suite_a[i];
    i--;
    }
 
    return(approx);
}
 
// affichage de fraction continue 
void fc_affiche(vector<int> &suite_a)
{
    cout << "a = [ ";
    for (auto & ele : suite_a)
    {
        if(ele > 0)
        cout <<ele << ", ";
    }
    cout << " ]" << endl;
     
}
// menu de Tp
void menu(){
    cout<<"########## Fractions Continues ###########"<<endl;
    cout<<"1:calcule fraction continue d'un numbre rationnel"<<endl;
    cout<<"2:calcule fraction continue d'un numbre irrationnel"<<endl;
    cout<<"3:calcule approximation d'une fraction continue"<<endl;
    cout<<"saiser votre choix"<<endl;
    }
     
//fonction principale
int main()
{   
    vector<int> suite_a;
    int choix ,n;
    double reel ;
    vector<int> tab;
     
    menu();
    cin>>choix;
     
     
    switch(choix){
        case 1:
            cout<<"saiser votre nombre reel"<<endl;
            cin>>reel;
            fc_irrationnel(reel,10,suite_a);
            fc_affiche(suite_a);
            break;
        case 2:
            cout<<"saiser votre nombre reel"<<endl;
            cin>>reel;
            cout<<"donne votre itteration n : "<<endl;
            cin>>n;
            fc_irrationnel(reel,n,suite_a);
            fc_affiche(suite_a);
            break;
        case 3:
            cout<<"approxiamation de fraction continues"<<endl;
            cout<<"donne combien nombre "<<endl;  
            cin>>n;
            for(int i=0;i<n;i++){
                cout<<"donne les nombre "<<i+1<<" : ";
                cin>>reel;
                tab.push_back(reel);
                }
            cout << "Approximation : " << fc_approx(tab) << endl;
            break;
        }
         
 
 
    return(0);
}
