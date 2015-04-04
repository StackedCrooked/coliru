#include <vector>
#include <numeric>
#include <iterator>
#include <iostream>
 
using namespace std; 

bool simetrico(vector<int>v){
    int i=0, j=v.size()-1;
    	while(i<j){
        	if (v[i++] != v[j--]) return false;
	}
    	return true;
}

int main (int argc, char *argv[]) 
{ 

	vector<int> vec;

	int n = 0;
	char salir = 's';

	do{ 
				
		cout<<"Ingrese un numero: "; 
		cin>>n; 
		vec.push_back(n);
		cout<<"¿Desea Continuar Escribiendo Numeros? s/n: ";
		cin>>salir;

	}while(salir!='n');


	for (int i : vec ) {
    		cout << i;
		cout<<" ";
	}

	if (simetrico(vec)){
	cout<<"El vector es simetrico"<<endl;
	}
    	else {
	cout<<"El vector no es simetrico"<<endl;
	}

  	return 0;
}