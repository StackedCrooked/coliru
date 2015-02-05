#include <iostream>
#include <cstring>

using namespace std;

class listino{
    private:
       char prod[30];
       double prezzo;
    public:
       listino(){
           strcpy(prod, " ");
           prezzo = 0;
       }
       listino (int p, char a[]){
           strcpy(prod, a);
           prezzo = p;
       }
       int prezzo_(char a[]){
           if (strcmp (a, prod) == 0) return prezzo;
           else return 0;
       }
    };
    
class cassaAutomatica{ public: listino{
    private:
        double totale;
    public: 
        cassaAutomatica(){
            totale = 0;
        }
        cassaAutomatica(int tot){
            totale = tot;
        }
    double prodotto(char a[]){
        if (prezzo_(a) > 0) { 
            totale = totale + prezzo_(a);
            return totale;
        }
        else cerr << "prodotto non in listino";
        return 0;
    }
    int paga(int euro){
        double resto;
        if (euro >= totale){
            resto = euro - totale;
            return resto;
        }
        else totale = euro - totale;
        return totale;
        }
};

int main()
{
    int b[9] = {1, 2, 3, 4, 5, 6, 7};
    somma_interi(b, 9);
    
    return (0);
}
}
