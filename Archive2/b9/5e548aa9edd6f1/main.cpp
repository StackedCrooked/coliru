#include <iostream>

class Vector{
    double* elem;
    int sz;
public:
    Vector(int s):elem{new double[s]}, sz{s} { for(int i = 0; i != sz; ++i) elem[i]= 0; }
    ~Vector() { delete[] elem; }
    double& operator[](int i) { return elem[i]; }
    int size() const { return sz; }
};

class Container{
public:
    virtual double& operator[](int i) = 0;
    virtual int size() const = 0;
    virtual ~Container() {}
};

class Vector_container:public Container{
    Vector v;
public:
    Vector_container(int s): v{s}{}
    ~Vector_container() }{}
    double& operator[](int i) { return v[i]; }
    int size() const {return v.size(); }
};

