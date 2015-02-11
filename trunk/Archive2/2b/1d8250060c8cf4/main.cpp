#include <iostream>
#include <string>

using namespace std;

template <class T>
class Intervall;

template<class T>
ostream& operator<<(ostream& os, Intervall<T>& iObj);

template<class T>
    Intervall<T> makeNewIntervall(T i, T s);

template<class Lhs, class Rhs> 
    auto operator+(Lhs lhs, Rhs rhs) -> decltype(lhs.getInf()+rhs.getInf());

template<class T>
class Intervall {
protected:
    T inf;
	T sup;

public:
	Intervall(T i=0, T s=0) : inf(i), sup(s) { }
	T getInf() { return inf; }
	T getSup() { return sup; };
    
    friend ostream& operator<< <>(ostream& os, Intervall& iObj);
    friend Intervall operator+ <>(Intervall lhs, Intervall rhs);
};

template<class T>
ostream& operator << (ostream& os, Intervall<T>& iObj)
{
    os << "[" << iObj.getInf() << ",";
    os << iObj.getSup() << "]";
    return os;
}
template<class Lhs, class Rhs> 
    auto operator+(Lhs lhs, Rhs rhs) -> decltype(lhs.getInf()+rhs.getInf())
	{
        return makeNewIntervall( lhs.getInf()+rhs.getInf(), lhs.getSup()+rhs.getSup());
	}
template<class T>
    Intervall<T> makeNewIntervall(T i, T s) { return Intervall<T>(i,s); }

int main()
{
	auto val1 = makeNewIntervall(0,2);
	auto val2 = makeNewIntervall(2.4,4.7);
    cout << val1 << " " << val2;
	//auto val3 = val1+val2;
	//cout << "[" << val3.getInf() << "," << val3.getSup() << "]";
	
	return 0;
}