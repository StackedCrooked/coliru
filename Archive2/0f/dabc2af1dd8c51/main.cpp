#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
class dynArray;

template<typename T>
ostream& operator<<(ostream& os,const dynArray<T>& A);

template<typename T>
class dynArray {
    int size;
    T* ptr;
    public:
    dynArray(int n=0);
    ~dynArray();
    T& operator[] (const int index);
    friend ostream& operator<< <T>(ostream& os, const dynArray& A);
    };

template<typename T> dynArray<T>::dynArray(int n):size(n){
if (size==0)
{
 cout << "Size Zero"<< endl;
 ptr=NULL;}
 else
 {
     try{
         ptr = new T[size];
         cout << "Constructor Called" << endl;
         }
     catch(bad_alloc xa)
     {
         cout << "Allocation Failure" <<endl;
         exit(EXIT_FAILURE);
         }
     }
}

template<typename T> dynArray<T>::~dynArray(){
    cout << "Destructor Called for array of size : " << size << endl;
    delete[] ptr;
    }

template<typename T> T& dynArray<T>::operator[] (const int index){
    assert(index >=0 && index <size);
    return *(ptr+index);
    }

template<typename T> ostream& operator<< (ostream& os,const dynArray<T>& A){
    for (int i=0; i < A.size ; i++)
    os << *(A.ptr+i) << " ";
    return os;
    }

int main()
{
    dynArray<int> array1;
    dynArray<int> array2(5);

    array2[0]=15;
    array2[3]= 45;

    cout << array2 << endl;
}
