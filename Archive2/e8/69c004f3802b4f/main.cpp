    #include <iostream>
    #include <cmath>
    
    using namespace std;
    
    float round(float f,float pres) {
        return (float) (floor(f*(1.0f/pres) + 0.5)/(1.0f/pres));
    }
    
    int main() {
        
    	cout << "17.589 -> " << round(17.589,0.005) << std::endl;
                                          // ^^^^^ Note that additional zero!
    	cout << "11.2125 -> " << round(11.2125,0.005) << std::endl;
    	return 0;
    }
