#include <cmath>
#include <iostream>   
#include <cstring>
//#include <array>
//#include <stdio.h>
//#include <algorithm>
//#include <vector>
//#include <iomanip>
//#include <cfloat>

//#include <boost/array.hpp>
//#include <boost/function.hpp>
//#include <boost/bind.hpp>
//#include <boost/math/special_functions/fpclassify.hpp>


//Parametri in ingresso:
// a1,l1,d1: parametri DH modificata del primo asse di rotazione
// a2,l2,d2: parametri DH modificata del secondo asse di rotazione
// q1,q2: posizione degli assi di rotazione

// x,y,z: posizione degli assi traslazionali

// tx,ty,tz: traslazione utensile
// px,py,pz: coordinate punta utensile rispetto all'origine


void forward_kin_head_head(double a1,double a2,
    					double l1,double l2,
						double d1,double d2,
						double q1,double q2,
						double tx, double ty, double tz,
						double x, double y, double z,
						double& px,double& py,double& pz)
{
	px=x-sin(q1)*(-sin(a2)*tz+cos(a2)*cos(q2)*ty+cos(a2)*sin(q2)*tx-sin(a2)*d2)+cos(q1)*(-sin(q2)*ty+cos(q2)*tx+l2)+l1;
	py=y+cos(a1)*cos(q1)*(-sin(a2)*tz+cos(a2)*cos(q2)*ty+cos(a2)*sin(q2)*tx-sin(a2)*d2)-sin(a1)*(cos(a2)*tz+sin(a2)*cos(q2)*ty+sin(a2)*sin(q2)*tx+cos(a2)*d2)+cos(a1)*sin(q1)*(-sin(q2)*ty+cos(q2)*tx+l2)-sin(a1)*d1;
	pz=z+sin(a1)*cos(q1)*(-sin(a2)*tz+cos(a2)*cos(q2)*ty+cos(a2)*sin(q2)*tx-sin(a2)*d2)+cos(a1)*(cos(a2)*tz+sin(a2)*cos(q2)*ty+sin(a2)*sin(q2)*tx+cos(a2)*d2)+sin(a1)*sin(q1)*(-sin(q2)*ty+cos(q2)*tx+l2)+cos(a1)*d1;
}



void inv_kin_head_head(double a1,double a2,
						double l1,double l2,
						double d1,double d2,
						double q1,double q2,
						double tx, double ty, double tz,
						double px,double py,double pz,
						double& x, double& y, double& z)
{
    x = -cos(q2)*(sin(a1)*sin(q1)*tz+cos(a1)*sin(q1)*ty+cos(q1)*tx-l1*cos(q1))-cos(a2)*sin(q2)*(sin(a1)*cos(q1)*tz+cos(a1)*cos(q1)*ty-sin(q1)*tx+l1*sin(q1))-sin(a2)*sin(q2)*(cos(a1)*tz-sin(a1)*ty-d1)+l2*cos(q2)+px;
    y = sin(q2)*(sin(a1)*sin(q1)*tz+cos(a1)*sin(q1)*ty+cos(q1)*tx-l1*cos(q1))-cos(a2)*cos(q2)*(sin(a1)*cos(q1)*tz+cos(a1)*cos(q1)*ty-sin(q1)*tx+l1*sin(q1))-sin(a2)*cos(q2)*(cos(a1)*tz-sin(a1)*ty-d1)-l2*sin(q2)+py;
    z = sin(a2)*(sin(a1)*cos(q1)*tz+cos(a1)*cos(q1)*ty-sin(q1)*tx+l1*sin(q1))-cos(a2)*(cos(a1)*tz-sin(a1)*ty-d1)+pz+d2; 
}


void callf(const double param[14]){
    double evals[3];
	
	double p[14];
	std::memcpy(p,param, sizeof(double[14]));
    for (int i = 0; i<14; ++i)
        std::cout << p[i] << '\t';
    std::cout << std::endl;
	inv_kin_head_head(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11],p[12],p[13],evals[0],evals[1],evals[2]);
    std::cout << "joints " << evals[0] << "\t\t" << evals[1] <<"\t\t" << evals[2] << "\t\t" << std::endl;
    p[11] = evals[0]; // x
    p[12] = evals[1]; // y
    p[13] = evals[2]; // z
    for (int i = 0; i<14; ++i)
        std::cout << p[i] << '\t';
    std::cout << std::endl;
    forward_kin_head_head(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11],p[12],p[13],evals[0],evals[1],evals[2]);
    std::cout << "opersp " << evals[0] << "\t\t" << evals[1] <<"\t\t" << evals[2] << "\t\t" << std::endl;
}

void paramf(){
    // DH params
    const double a1 = -1;	const double a2 = 0.5;
	const double l1 = 2;	const double l2 = 1;
	const double d1 = 1;	const double d2 = 1;
    double P[] = {0,0,0,0,0}; // px,py,pz,q1,q2
	//for (int i = 0; i <= 30; ++i){
		double par[] = {a1,a2,l1,l2,d1,d2,P[3],P[4],0,0,0,P[0],P[1],P[2]};
		callf(par);
	//}
}



int main()
{
    paramf();
    return 0;
}


