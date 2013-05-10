/*compiled with: »g++ UZ03_Pfeiler_Stepanov.cpp -std=c++11 -o nulladdition«
nulladdition 5 100 float
exp_recu: 148.4131622314453125
exp_iter: 148.4131622314453125
std::exp: 148.41315910257659993
diff: -3.12886871256523591e-006

nulladdition 5 100 double
exp_recu: 148.41315910257659993
exp_iter: 148.41315910257659993
std::exp: 148.41315910257659993
diff: 0

nulladdition -10 100 float
exp_recu: -5.2342282288009300828e-005
exp_iter: -5.2342282288009300828e-005
std::exp: 4.5399929762484854173e-005
diff: 9.7742212050494155001e-005

nulladdition -10 100 double
exp_recu: 4.5399929670400209413e-005
exp_iter: 4.5399929670400209413e-005
std::exp: 4.5399929762484854173e-005
diff: 9.208464475966501861e-014
*/
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

template<typename T>
inline T yn(const T x, const T n) {
    if(n<=0) throw std::invalid_argument("invalid argument n<=0 \nwhile calling yn(T, T)");
	return n<=1? x: (x/n *yn(x, n-1));
}

template<typename T>
inline T fn(const T x, const T n) {
	if(n<=0) throw std::invalid_argument("invalid argument n<=0 \nwhile calling fn(T, T)");
	return n<=1? 1+yn(x, T{1}): (fn(x, n-1)+yn(x, n));
}

template<typename T>
inline T exp(const T x, const int i) {
	if(i<=0) throw std::invalid_argument("invalid argument i<=0 \nwhile calling exp(T, int)");
	T ynprev = x;
	T fnprev = 1 + ynprev;
	for(int n = 2; n <= i; ++n) 
		(fnprev = fnprev + (ynprev = x/n *ynprev));
	return fnprev;
}

int main(int argc, char* argv[]) {
	try {
		int x, imax;
		std::string type;
		if(argc==4) {//read parameters
			x = std::stoi({argv[1]});
			imax = std::stoi({argv[2]});
			type = {argv[3]};
		}
		if(argc!=4 || (type!="float" && type!="double")) {//reversed program invariant
			std::cout << "Usage: " << argv[0] << " [x] [iterations] [float | double]" << std::endl;
			return 0;
		}
		long double approx, exact;
		std::cout << std::setprecision(20) << "exp_recu: " << (type=="float" ? fn<float>(x, imax) : fn<double>(x, imax)) << std::endl;
		std::cout << "exp_iter: " << (approx=(type=="float" ? exp<float>(x, imax) : exp<double>(x, imax))) << std::endl;
		std::cout << "std::exp: " << (exact=std::exp(x)) << std::endl;
		std::cout << "diff: " << exact-approx << std::endl;
	} catch(std::exception& ex) {//L"An Exception was caused while executing the program"
		#ifdef _WIN32
		MessageBoxA(nullptr, ex.what(), "Fatal Error", MB_ICONERROR);
		#else
		throw ex;
		#endif
	}
}