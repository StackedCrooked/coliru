#include <algorithm> 
#include <iostream>
#include <vector>

using namespace std;

struct Mweather {
    double high_temperature;
    double low_temperature;
};

double highestTempOfYear(Mweather data[12]){
        vector<double> temps;
        for(int i = 0; i < 12; i++){
            temps.push_back(data[i].high_temperature);
            temps.push_back(data[i].low_temperature);
        }
         return *max_element(temps.begin(),temps.end());
    }

double lowestTempOfYear(MWeather data[12]){
    vector<double> temps;
    for(int i = 0; i < 12; i++){
        temps.push_back(data[i].high_temperature);
        temps.push_back(data[i].low_temperature);
    }
    
int main() {
    
}