#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void afficher_sup(int T[], const int n, int sup){    
    for(int i = 0; i < n; i++){
        if(T[i] >= sup)
            cout << T[i] << " ";
    }
    cout << endl;
}

void remplir_rnd(int T[], const int n, int min, int max){
    srand(time(0));
    for(int i = 0; i < n; i++){
        T[i] = min + rand()%(max - min + 1);
    }
}

void remplir(int T[], const int n, const int a){    
    for(int i = 0; i < n; i++){
        T[i] = a;
    }
}

void appartient_au(int T[], const int n, const int V){  
    bool flag = false;
    for(int i = 0; i < n; i++){
        if(T[i] == V)
            flag = true;            
    }
    
    if(flag)
        cout << V << " se trouve dans le tableau" << endl;
    else
        cout << V << " ne se trouve dans le tableau" << endl;
}

int find_sup(int T[], const int n){  
    int sup = -100;
    int ind_sup = -1;
    for(int i = 0; i < n; i++){
        if(T[i] > sup){
             sup = T[i];
             ind_sup = i;
        }
    }
    
    if(ind_sup >= 0)
        cout << "Indice du plus grand element : " << ind_sup << endl;
        
    return ind_sup;
}

void supprime(int T[], const int n, int V){  
    bool flag = true;
    for(int i = 0; i < n && flag; i++){
        if(T[i] == V){
            flag = false;
            for(int j = i; j < n - 1; j++){
                T[j] = T[j+1];
            }
            T[n-1] = 0;
        }
    }
    
    for(int i = 0; i < n; i++){
        cout << T[i] << " ";
    }
    cout << endl;
}

void insere(int T[], const int n, int V, int pos){
    
    if(pos >= 0 && pos < n){
        for(int j = n - 1; j > pos; j--){
            T[j] = T[j-1];
        }
        T[pos] = V;            
            
        for(int i = 0; i < n; i++){
            cout << T[i] << " ";
        }
        cout << endl; 
        
    }else{
        cout << "Indice non valable " << endl;
    }
        
    
}


int main()
{   
    const int n = 10;
    const int max = 50;
    const int min = 5;
    const int V = 15;
    
    int Tableau[n];
    cout << "Exercice TABLEAUX" << endl;
    remplir_rnd(Tableau, n, min, max);
    afficher_sup(Tableau, n, 1);
    
    appartient_au(Tableau, n, V);
    //int indsup = find_sup(Tableau, n);
    //supprime(Tableau, n, Tableau[indsup]);
    insere(Tableau, n, 5, 18);
    //cout << "Inserez 10 entier apres le enter:" << endl;
    //for(int i = 0; i < n; i++){
    //    cin >> Tableau[i];
    //}
    //affiche_sup(Tableau, n, 10);
    
    
   
   return 0;
}