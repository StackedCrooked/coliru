#include <iostream>
#include <cmath>
using namespace std;


const double PI = 3.141592654;
const double Na = 6.022141e23; // 1/mol
const double Re = 2.818e-15; // m
const double Me = 0.51; // MeV/c2
const double M_alpha = 3.727*1000;
const double R_Al = 2700; // kg/m3
const double F_Fe = 7870;
const double R_air = 1.200; // kg/m3 1 atm 20 C
const double R_air_6 = R_air*51325/101325.; // - wskazanie na ciśnieniomierzu "-0.05 MPa" zatem licznik 101325-0.05e6
const double A_Al = 0.026982; // kg
const double A_Fe = 0.05585;
const double A_N = 0.014;
const double A_O = 0.016;
const int Z_Fe = 26;
const int Z_Al = 13;
const int Z_N = 7;
const int Z_O = 8; 
const int Z_Ar = 18;
const int Z_C = 6;
const int z_alpha = 2; // ladunek czastki alfa

// sklad powietrza
const double p_N = 78084.0;
const double p_O = 20946.0;

double ionz_sqr(int Z) {
    double result = 0.0;
	if (Z<13)
		result = 12.0*Z + 7;
	else
		result = 9.76*Z + 58.8*pow(Z, -0.19);
	return result*result*1e-12;
}

double gamma_sqr(double en) {
	double result = 1.0+en/M_alpha;
	return result*result;
}

double betha_sqr(double en) {
	return 1.0 - 1.0/gamma_sqr(en);
}

double W_max(double en) {
	return 2.0*Me*betha_sqr(en)*gamma_sqr(en);
}

double dE(double dx, int Z, double A, double en, double R) {
	// R gestosc absorbentu
	// Z liczba atomowa absorbentu
	double result = -dx*2*PI*Na*Re*Re*Me*R*Z*z_alpha*z_alpha/(A*betha_sqr(en));
		   result *= log(2*Me*gamma_sqr(en)*betha_sqr(en)*W_max(en)/ionz_sqr(Z)) - 2.0*betha_sqr(en); 
	return result;
}


const double ds[] = {0.000008, 0.00000887, 0.0000097, 0.00000804, 0.00000843, 0.0000092, 0.00000685, 0.00000718, 0.00000681, 0.0000072, 0.00000714, 0.00001405, 0.00001434, 0.00001432, 0.00001604, 0.00001770, 0.00001890, 0.00001485, 0.00001601, 0.00001690}; // grubosc aluminium
const double ps[] = {0.00134, 0.002, 0.004, 0.006, 0.008, 0.01, 0.012, 0.014, 0.016, 0.018, 0.020, 0.022, 0.024}; // dystans w powietrzu



int main() {

	double E, step, abs_width;
	
	// Al
	cout << "**************************************************************************" << endl;
    cout << "Aluminium: "<<endl;
    E = 4.65;
    step = 0.0000001;
	abs_width = 0.000020; // jednostka m
	cout << 0.0 << "   " << E << endl;
    for (double x=0; x<=abs_width; ) {
        x+=step;
		E+=dE(step, Z_Al, A_Al, E, R_Al);
		cout << x << "   " << E << endl;
	}	
	//cout << "Aluminium: "<<E<<endl;


    // powietrze
	cout << "**************************************************************************" << endl;
    cout << "Powietrze: "<<endl;
    E=4.65;
    step = 0.001;
    abs_width = 0.055; // jednostka m
    cout << 0.0 << "   " << E << endl;
    for (double x=0; x<=abs_width; ) {
        x+=step;
    	double temp=p_O*A_O*dE(step,Z_O,A_O,E,R_air_6) + p_N*A_N*dE(step, Z_N, A_N, E, R_air_6);
		E+= temp/(p_O*A_O + p_N*A_N);
        cout << x << "   " << E << endl;
	}
	//cout << "Powietrze: "<<E<<endl;


	// Al zadane grubosci
    cout << "**************************************************************************" << endl;
    for (unsigned i=0; i<sizeof(ds)/sizeof(double); ++i) {
		E=4.65;
		step = 0.00000001;
		abs_width = ds[i];
		for (double x=0; x<=abs_width; x+=step) {
			E+=dE(step, Z_Al, A_Al, E, R_Al);
		}
		cout << "Aluminium grubosc= " << ds[i] << " E = " << E << endl;
	}
	
	// powietrze
    cout << "**************************************************************************" << endl;
    for (unsigned i=0; i<sizeof(ps)/sizeof(double); ++i) {
		E=4.65;
		step = 0.00001;
		abs_width = ps[i];
		for (double x=0; x<=abs_width; x+=step) {
			double temp=p_O*A_O*dE(step,Z_O,A_O,E,R_air_6) + p_N*A_N*dE(step, Z_N, A_N, E, R_air_6);
			E+= temp/(p_O*A_O + p_N*A_N);
		}
		cout << "Powietrza odleglosc = " << ps[i] << " E = " << E << endl;
	}
	
	
}