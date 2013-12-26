 #include <iostream>
 #include <string>
 #include <cmath>
 
 int main() {

    std::string line;
    int input = 0;
    int broj_rijeci = 0;
    line = "[311]";
    if (line.at(0) == '[')
    {
        int i = line.length() - 2;
        int brojac = 0;
        while (line.at(i) != line.at(0))
        {
            input = line.at(i);
            input -= 48; //ascii_convert(input);
            broj_rijeci = broj_rijeci + input * pow(10, brojac);
            i--;
            brojac++;
        }
    }
    
    std::cout << broj_rijeci << std::endl;
    
}