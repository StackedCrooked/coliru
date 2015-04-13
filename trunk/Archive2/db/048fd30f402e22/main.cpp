#include <vector>
#include <iostream>

using namespace std;

vector<int> rec(vector<int> victor,int restan,int casette, int h, int k,int cont, vector<int> sirven){
    int largo = victor.size();
	//ver si añadir vector<int> sirven;
	cont=cont + 1; //ej: 1, 2 , 3, 4 para victor{8, 2, 3, 5}
	cout <<"sd";
	if (h==0){
		restan = casette - (victor[h] + victor[k]);
		if (restan==0){
			sirven.push_back(h); //se añaden los indices del vector victor al final
			sirven.push_back(k);
			return sirven;
		}

		else if (restan>0){
			sirven[0]=restan;
			sirven.push_back(h);
			sirven.push_back(k);
			restan = restan - rec(victor, restan, casette, h, k+1, cont,sirven)[0];
		}

		else{
			restan = restan + victor[k];
			if (cont<largo)
				restan = restan - rec(victor, restan, casette, h, k+1, cont,sirven)[0];//verificar si es k+1 o k+2
			else if (cont==largo)
				return sirven;
		}
	}

	else if (k<largo) {
		restan = restan - victor[k];

		if (restan>0)
			sirven[0] = restan;
			sirven.push_back(k);
			if (cont<largo)
				restan = restan - rec(victor, restan, casette, h, k+1, cont,sirven)[0];
			else if (cont==largo)
				return sirven;
			//else
				//nunca pasa (creo) --> eliminar

		else if (restan==0){
			sirven[0] = restan;
			sirven.push_back(k);
			return sirven;
		}

		else{
			restan = restan + victor[k];
			if (cont<largo)
				restan = restan - rec(victor, restan, casette, h, k+1, cont,sirven)[0];//verificar si es k+1 o k+2
			else if (cont==largo)
				return sirven;
		}
	}

	else if (k==largo){
		//k vuelve al termino inicial

		if (cont<largo){
			restan = restan - victor[0];
			if (restan>0){
				sirven.push_back(0);
				sirven[0] = restan; 
				restan = restan - rec(victor, restan, casette, h, 1, cont,sirven)[0];
			}
			else if (restan==0){
				sirven.push_back(0);
				sirven[0] = restan;
				return sirven;
			}
			else{
				restan = restan + victor[0];
				restan = restan - rec(victor, restan, casette, h, 1,cont,sirven)[0];
			}
		}
		else if (cont==largo){
			restan = restan - victor[0];
			if (restan>=0){
				sirven.push_back(0);
				sirven[0] = restan;
				return sirven;
			}
			else{
				return sirven;
			}
	
		}
	}

	/* else if (k>largo){
		//en el caso de k+2}

	NUNCA IMPRIMIR EN FUNCION*/

	return sirven ;
}

int main(){
	int casette=10;
	vector<int> victor; //vector solo con cancion (no incl. duracion del casette)
	vector<int> sirven; //el retornado
	sirven.push_back(0); 
	vector<int> s_max; //el mas optimo
	vector<int> s_actual;
	victor.push_back(8);
	victor.push_back(2);
	victor.push_back(3);
	victor.push_back(5);
	s_max.insert(s_max.begin(),0);
	int n,y;
	int m = victor.size();
	int u = s_max.size();

	//comprueba fila por fila 
	for (n=0; n<m; n++){
	cout<<"holi"<<endl;

		//evaluar si eliminar 3era variable casette
		s_actual = rec(victor,casette, casette, n, 0,0,sirven);

		if (s_actual[0]>=s_max[0]){
			s_max.resize(0);
			s_max.swap(s_actual); //ver si funciona, o copiarlo con un for y limpiar s_actual
			s_actual.resize(0);
		}
		else {
			s_actual.resize(0);
		}
		//ve si cambiar el mayor
	}
	cout<<"ftg";
	for (y = 0; y<u; y++){
		cout << "perra" << endl;
		cout << victor[s_max[y]] << " ";
	cout << "duracion:" << casette - s_max[0] << endl; 
	}
	return 0;
}