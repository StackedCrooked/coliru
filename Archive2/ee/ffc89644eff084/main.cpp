#include <iostream>
#include <string>
#include <vector>
#include <boost/any.hpp>

template<class T>
class MyTemplateClass{
public:
     void saveData(T *data);
private:
    T *my_data;
};

template<class T>
void MyTemplateClass<T>::saveData(T *data){
    *my_data = *data;
}

class LibraryUser{
public:
    void saveDoubleData(double *data);
    void saveFloatData(float *data);
private:
    MyTemplateClass<boost::any> my_generic_object;
};

void LibraryUser::saveDoubleData(double *data)
{
    my_generic_object.saveData(data);
}

void LibraryUser::saveFloatData(float *data)
{
    my_generic_object.saveData(data);
}

int main()
{
    LibraryUser user;
	double d[2] = {1.1111, 2.222222};
    user.saveDoubleData(d);
    
	float f = 9.9999f;
    user.saveFloatData(&f);
}