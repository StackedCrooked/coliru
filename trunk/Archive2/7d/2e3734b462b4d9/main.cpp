#include <iostream>
#include <string>
using namespace std;

class Spia{
    public:
    Spia() {
        cout << "Creazione Spia"<<endl;
    }
    ~Spia() {
        cout << "Fine Spia"<<endl;
    }
};

class Oggetto{
    public:
        //Oggetto(const string& stringa):
        Oggetto(const Spia& stringa):
        stringa(stringa)
        {
            cout << "Creazione Oggetto"<<endl;
        }
        ~Oggetto(){
            cout <<"Fine Oggetto"<<endl;
        }
        void operazione(){
            cout << "Operazione"<<endl;
        }
        
    const Spia& stringa;
    
};

int main()
{
    cout << "test" <<endl;
    auto x = Oggetto(Spia());
    x.operazione();
    cout << "fine test" <<endl;
}
