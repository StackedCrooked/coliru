#define kelvinToCelc(k) k - 273.15
#define celcToFahren(c) (9.0 / 5.0) * c + 32

int main() {
    const double absoluteTemp = 373.15;
    
    double x = kelvinToCelc(absoluteTemp);              // 100
    double y = celcToFahren(x);                          // 212
    double z = celcToFahren(kelvinToCelc(absoluteTemp)); // 430.52???
    
    celcToFahren(kelvinToCelc(absoluteTemp));
}