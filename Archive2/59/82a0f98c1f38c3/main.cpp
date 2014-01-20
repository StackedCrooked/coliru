#include <iostream>
#include <math.h>

/**
\brief: compute the maximum curvature of the Quadratic Bezier curve
*/
static double calcMaximumCurvature(const double p0[], const double p1[], const double p2[], unsigned int N){
    volatile double maximum_curvature = 0.;
	unsigned int i;
	double area = 0.;
	double p0p2 = 0.;
	double p0p1 = 0.;

	double height = 0.;
	double cos_alfa = 0.;
	unsigned int isInternal = 0;

	for(i = 0; i < N; ++i){
		p0p2 += (p2[i]-p0[i])*(p2[i]-p0[i]);
		p0p1 += (p1[i]-p0[i])*(p1[i]-p0[i]);
		cos_alfa += (p2[i]-p0[i])*(p1[i]-p0[i]);
	}
	p0p2 = sqrt(p0p2);
	p0p1 = sqrt(p0p1);
	cos_alfa /= (p0p2*p0p1);

	height = p0p1*sqrt(1-cos_alfa*cos_alfa);
	area = p0p2*height/2.;

	//is p1 internal to the circle having diameter p1-m and center lying on the p1-m segment?
	if(isInternal == 0){
		double distance_from_center = 0.;
		double tmp = 0.;
		
		for(i = 0; i < N; ++i){
			tmp = p1[i] - ( p0[i] + (p2[i]-p0[i])/4. );
			distance_from_center += tmp*tmp;
		}
		distance_from_center = sqrt(distance_from_center);

		if(distance_from_center <= p0p2/4.)
			isInternal = 1;
	}

	//is p1 internal to the circle having diameter p2-m and center lying on the p2-m segment?
	if(isInternal == 0){
		double distance_from_center = 0.;
		double tmp = 0.;
		
		for(i = 0; i < N; ++i){
			tmp = p1[i] - ( p2[i] + (p0[i]-p2[i])/4. );
			distance_from_center += tmp*tmp;
		}
		distance_from_center = sqrt(distance_from_center);

		if(distance_from_center <= p0p2/4.)
			isInternal = 1;
	}

	/*
	A is the area of the triangle p0 p1 p2
	m is the midpoint between p0 and p2

		---- Theorem (Deddi, Everett, Lazard) ----
	The maximum curvature of a quadratic Bezier is either equal to |p1 m|^3/A
	if p1 lies strictly outside the two disks of diameter p0 m and m p2,
	or is equal to max(k0, k1) where k0 = A/|p0 p1|^3 and k1 = A/|p1 p2|^3
	are the curvature at the endpoints.
	*/
	if(isInternal == 0){
		double tmp = 0.;
		maximum_curvature = 0.;
		for(i = 0; i < N; ++i){
			tmp = p1[i] - ( p0[i] + (p2[i]-p0[i])/2. );
			maximum_curvature += tmp*tmp;
		}
		maximum_curvature = sqrt(maximum_curvature);
		maximum_curvature = (maximum_curvature*maximum_curvature*maximum_curvature)/(area*area);
	}else{
		double tmp = 0.;
		double k0 = 0.;
		double k1 = 0.;
		for(i = 0; i < N; ++i){
			tmp = p1[i] - p0[i];
			k0 += tmp*tmp;
			tmp = p2[i] - p1[i];
			k1 += tmp*tmp;
		}

		k0 = sqrt(k0);
		k0 = area/( k0*k0*k0 );
		k1 = sqrt(k1);
		k1 = area/( k1*k1*k1 );

		if(k0 > k1)
			maximum_curvature = k0;
		else
			maximum_curvature = k1;
	}
	return maximum_curvature;
}

double simpleabs(double v){
    return abs(v);
}

unsigned short computeMaxVelAcc(const double maximum_curvature, double* desired_speed, double* desired_acc, const double maximum_allowed_acc){
    double desired_acc_squared = (*desired_acc)*(*desired_acc);
	double desired_speed_to_the_fourth = (*desired_speed)*(*desired_speed)*(*desired_speed)*(*desired_speed);
	double curvature_squared = maximum_curvature*maximum_curvature;
	double acceleration_module = sqrt(  desired_acc_squared + desired_speed_to_the_fourth*curvature_squared );
	double ratio = acceleration_module/simpleabs(maximum_allowed_acc);
	if(ratio <= 1.)
		return 1;
	*desired_speed = *desired_speed/sqrt(ratio);
	*desired_acc = *desired_acc/ratio;
	return 0;
}

int main() {
    {
        const double p0[] = {0., 0.};
        const double p1[] = {100., 0.};
        const double p2[] = {100., 1.};
        
        const double curvature = calcMaximumCurvature(p0, p1, p2, sizeof(p0)/sizeof(p0[0]));
        
        double desired_speed = 5.;
        double desired_acc = 50.;
        computeMaxVelAcc(curvature, &desired_speed, &desired_acc, 51.);
        
        using namespace std;
        cout << "curvature:" << curvature << endl;
        cout << "speed: " << desired_speed << ", acc: " << desired_acc << endl;
    }
    
    {
        const double p0[] = {0., 0.};
        const double p1[] = {100., 0.};
        const double p2[] = {100., 100.};
        
        const double curvature = calcMaximumCurvature(p0, p1, p2, sizeof(p0)/sizeof(p0[0]));
        
        double desired_speed = 5.;
        double desired_acc = 50.;
        computeMaxVelAcc(curvature, &desired_speed, &desired_acc, 51.);
        
        using namespace std;
        cout << "curvature:" << curvature << endl;
        cout << "speed: " << desired_speed << ", acc: " << desired_acc << endl;
    }
}