#include <string>
#include <iostream>

struct Fr 
{
    int num;
    int denom;
    Fr(int i,int j)
    {
        num=i;
        denom=j;
    }
    Fr(){};
    
    operator std::string()
    {
        return (std::to_string(num) + "/" + std::to_string(denom));
    }
};

std::ostream& operator<< (std::ostream& o, const Fr& f) {
    o << f.num << '/' << f.denom;
    return o;
}

int main() {
    Fr f (4, 9);
    std::string s = f;
    std::cout << s << std::endl;
    std::cout << f << std::endl;
    return 0;
}