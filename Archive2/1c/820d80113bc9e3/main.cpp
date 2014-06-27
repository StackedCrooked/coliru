#include <iostream>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;

template<typename T>
class Vector {
private:
    T * elems;
    size_t size_;
public:
    Vector (size_t n) : elems {new T[n]}, size_ {n} 
    {   cout << "ctor 1 called\n";
        for (size_t i = 0; i < n; i++)
        {   elems[i] = 0; /* what is default(T)? */   }   }
        
    Vector (const vector<T> & those) 
    {   cout << "ctor 2 called\n";
        this->size_ = those.size();
        this->elems = new T[this->size_];
        for (auto i = ((size_t)0); i < this->size_; i++)
        {   this->elems[i] = those[i];   }   }
        
    ~Vector () 
    {   cout << "dtor called\n";
        delete [] elems; size_ = 0;};
    
    const size_t size () const
    {   return this->size_;   }
    
    void print () const
    {   auto c = this->size();
        for (auto i = ((size_t)0); i < c; i++)
        {   cout << (0 == i ? "[" : ", ") << (*this)[i];   }
        cout << "]" << endl;   }
    
    T & operator[](size_t i)
    {   cout << "Non-const indexer called.\n" ;
        if (0 > i || this->size() <= i)
        {   cout << "Called with bogus index " << i << endl;
            throw out_of_range {"Vector::operator[]"};   }
        return this->elems[i];   }
        
    const T & operator[](size_t i) const
    {   cout << "Const indexer called.\n" ;
        if (0 > i || this->size() <= i)
        {   cout << "Called with bogus index " << i << endl;
            throw out_of_range {"Vector::operator[]"};   }
        return this->elems[i];   }
        
};

void print (const vector<double> & them)
{   auto c = them.size();
    for (auto i = ((size_t)0); i < c; i++)
    {   cout << (0 == i ? "[" : ", ") << them[i];   }
    cout << "]" << endl;   }

int main()
{   const double e = 2.718281828459045;
    const double pi = 3.14159265358979;
    const double gamma = 0.577215664901532;
    
    vector<double> them {1.11, e, pi};
    auto v = Vector<double> (them);
    v.print ();
    
    
    auto w = vector<double> (3);
    w[0] = sin(11.0);
    w[1] = 163 * (pi - e);
    w[2] = pow(e, pi) - pi;
    w.push_back (gamma);
    
    v = Vector<double> {w};
    v.print ();
//    print (w);
    
    cout << "goodbye.\n";
}
