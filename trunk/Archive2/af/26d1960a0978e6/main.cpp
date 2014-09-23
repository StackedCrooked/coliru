    #include <iostream>
    #include <cmath>
    #include <iomanip>
    
    using namespace std;
    
    float round(float f,float pres) {
        return (float) (floor(f*(1.0f/pres) + 0.5)/(1.0f/pres));
    }
    
    int main() {
        
    	cout  << "17.589 -> " << fixed << setprecision(2) << round(17.589,0.005) << std::endl;
    	cout << "11.2125 -> " << fixed << setprecision(2) << round(11.2125,0.005) << std::endl;
    	return 0;
    }
