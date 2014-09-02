#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

class Rationals{
private:
    double val;
public:
	Rationals(double szVal) : val{ szVal }{}
	Rationals() : val{ 0 }{}
	double GetVal(){
		return val;
	}
	void SetVal(double toSet){
		val = toSet;
	}

	double mul(Rationals x, Rationals y){
		return x.GetVal()*y.GetVal();
	}

	double sub(Rationals x, Rationals y){
		return x.GetVal()-y.GetVal();
	}

	double add(Rationals x, Rationals y){
		return x.GetVal() + y.GetVal();
	}

	double GetId(){
		return 1.0;
	}

	double GetZero(){
		return 0.0;
	}

	double up(int si){
		double u = -1;
		double z = u;

		if (si == 0){
			return 1;
		}

		for (int i = 0; i < (si-1); i++){
			z = z*u;
		}

		return z;
	}


};

template<typename T> 
class Matrix
{
    vector<vector<T>> mx; //Matriz nxm
	int n;
	int m;
	int Aux(int i, int si){
		if (i < si){
			return i;
		}
		return i - 1;
	}
public:
	Matrix(int szn, int szm) : mx(szn, vector<T>(szm)), n{ szn }, m{ szm }{}

	//getters-setters
	T Get(int i, int j){
		return (mx[i])[j];
	}

	void Set(int i, int j, T val){
		(mx[i])[j].SetVal(val.GetVal()); 
	}

	void MakeId(){
		T Id;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				if (i == j){
					(mx[i])[j].SetVal(Id.GetId());
				}
				else
				{
					(mx[i])[j].SetVal(Id.GetZero());
				}
			}
		}
	}
	//Miscellaneus stuff
	Matrix<T> GetTruncated(int si, int sj){
		Matrix<T> copy(n-1, m-1);
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				if ((i != si) && (j != sj)){
					copy.Set(Aux(i,si), Aux(j,sj), Get(i, j));
				}
			}
		}
		return copy;
	}
	
	void Show(){
		for (int i = 0; i < n; i++){
			cout << "\n";
			for (int j = 0; j < m; j++){
				cout << (mx[i])[j].GetVal() << " ";
			}
		}
	}

	int Sizex(){
		return m;
	}

	int Sizey(){
		return n;
	}

	T Det(){
		T res(0);
		if (n == 2){
			res.SetVal(res.sub(res.mul((mx[0])[0], (mx[1])[1]), res.mul((mx[1])[0], (mx[0])[1])));
			return res;
		}
		for (int j = 0; j < m; j++){
			Matrix<T> sm = GetTruncated(0, j);	
			T a = sm.Det();
			a.SetVal(a.mul(a, (mx[0])[j]));
			a.SetVal(a.mul(a, a.up(j)));
			res.SetVal(res.add(res, a));
		}
		return res;
	}

	// Operadores para matrizes
};

// template<typename T>
template<typename T>
Matrix<T> operator+(Matrix<T> A, Matrix<T> B){
	Matrix<T> D = A;
	

	if (A.Sizex() != B.Sizex() || A.Sizey() != B.Sizey()){
		// return nullptr;
        throw std::runtime_error("size mismatch");
	}

	for (int i = 0; i < A.Sizex(); i++){
		for (int j = 0; j < A.Sizey(); j++){
			T value = A.Get(i, j);
			value.SetVal(value.add(value.GetVal(), A.Get(i, j).GetVal()));
			D.Set(i, j, value);
		}
	}

	return D;
}

int main() {
    Matrix<Rationals> m(4,4);
        Rationals p(0);
//      const Rationals * z;
 
        p.SetVal(0);
        m.Set(0, 0, p);
        p.SetVal(1);
        m.Set(0, 1, p);
        p.SetVal(2);
        m.Set(0, 2, p);
        p.SetVal(45);
        m.Set(0, 3, p);
 
        p.SetVal(22);
        m.Set(1, 0, p);
        p.SetVal(1);
        m.Set(1, 1, p);
        p.SetVal(2);
        m.Set(1, 2, p);
        p.SetVal(3);
        m.Set(1, 3, p);
 
        p.SetVal(2);
        m.Set(2, 0, p);
        p.SetVal(3);
        m.Set(2, 1, p);
        p.SetVal(4);
        m.Set(2, 2, p);
        p.SetVal(-1);
        m.Set(2, 3, p);
 
        p.SetVal(-1);
        m.Set(3, 0, p);
        p.SetVal(-2);
        m.Set(3, 1, p);
        p.SetVal(3);
        m.Set(3, 2, p);
        p.SetVal(22);
        m.Set(3, 3, p);
        //m.Show();
 
        Matrix<Rationals> Nova = m;
 
        Nova.MakeId();
 
        Nova.Show();
        m.Show();
 
        Matrix<Rationals> Soma = m + Nova;
}
