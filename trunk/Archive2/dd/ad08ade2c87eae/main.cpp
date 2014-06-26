#include <iostream>

class Integer {
    friend std::ostream &operator <<(std::ostream &os, const Integer &integer);
    friend Integer operator +(const Integer &i1, const Integer &i2);
    friend Integer operator -(const Integer &i1, const Integer &i2);
    friend Integer operator *(const Integer &i1, const Integer &i2);

public:
    Integer(int val=0) : val(val) {}
    Integer &operator +=(const Integer &other);
    Integer &operator -=(const Integer &other);
    Integer &operator *=(const Integer &other);
private:
    int val;
};

using namespace std;

ostream &operator <<(ostream &os, const Integer &integer) {
    os << integer.val;
    return os;
}

Integer operator +(const Integer &i1, const Integer &i2) {
    Integer result = i1;
    return result += i2;
}

Integer operator *(const Integer &i1, const Integer &i2){

    Integer result =i1;
    return result *= i2;
}

Integer operator -(const Integer &i1, const Integer &i2){

    Integer result =i1;
    return result -= i2;
}

Integer &Integer::operator +=(const Integer &other) {
    val += other.val;
    return *this;
}

Integer &Integer::operator -=(const Integer &other) {
    val -= other.val;
    return *this;
}

Integer &Integer::operator *=(const Integer &other){
    val *= other.val;
    return *this;
}


#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    Integer i1, i2 = 10;

    cout << "i1: " << i1 << endl;
    cout << "i2: " << i2 << endl;

    cout << "i1: " << i1 << endl;
    cout << "i2: " << i2 << endl;
    cout << "i1 + i2: " << i1 + i2 << endl;

    i1 += i2;
    cout << "after i1 += i2 - i1: " << i1 << endl;

    cout << endl;

    /// Now we'll show the operators in their 'functional' form

    cout << "i1 + i2: " << operator +(i1, i2) << endl;

    i1.operator +=(i2);
    cout << "after i1.operator +=(i2) - i1: " << i1<<endl;

    Integer i3=2, i4=5;

    cout<<"i3:"<<" "<<i3<<endl;
    cout<<"i4:"<<" "<<i4<<endl;

    cout<<"i4*i3: "<< i4 * i3 <<endl;

    i3 += i4; 
    cout<<"After i3 += i4: "<<i3<<endl;
    cout<<i3<<i4;
    i3 *= i4;
    cout<<"After i3 *= i4: "<<i4<<endl;


    cout<<"opeartor *(i3, i4):   "<<operator *(i3, i4)<<endl;

    cout<<"operator i3.operator *=(i4):  "<<i3.operator*=(i4);




    return 0;
}