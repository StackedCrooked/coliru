#include <iostream>
#include <vector>
using namespace std;
template<class T>
 struct s{

    T val;

    public:
        s(T a = T())
        {
            val = a;
        };
        
        friend ostream& operator<<(ostream& os, const s<T>& a){
            return os << a.val;
        }
 };


int main()
{
    s <double> names(4) ;
    s <int> figure(7);
    s <string> word;
    s <vector<int>*> array;
    cout << names << endl;
    cout << figure << endl;
    cout << array << endl;
    return 0;
}