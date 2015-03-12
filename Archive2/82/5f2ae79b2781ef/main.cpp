#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Tocka {
    Tocka();
    Tocka(int, int);
    int x;    
};

int min;
Tocka temp;

double Najkraci(vector<Tocka> v){
    static vector<Tocka> a;
    static int broj = 0;
    int i;
    static double najmanja = 0;
    if (broj == 0) { //pocinjemo od rubne tocke
        for(std::vector<Tocka>::iterator it = v.begin() ; it != v.end(); ++it){
            if (it->x < min) {min = it->x; temp = *it;}
        }
        a.push_back(temp);
    }
    if (a.size() == v.size()) {cout <<najmanja; return najmanja;}
    i = 0;
    min = 1000;
najmanja = najmanja + min;
a.push_back(temp);
//cout << "Hrebak";
//cout << v.size() << ","<< a.size() << endl;
broj++;
najmanja = najmanja + Najkraci(v);
}

int main(){
int n,i;
double a,b;
vector<Tocka> t;
cin >> n;
for(i = 0; i < n; i++) {
    cin >> a >> b;
    Tocka temp(a,b);
    t.push_back(temp);
}
cout << "Najkraci put:" << Najkraci(t);

return 0;
}