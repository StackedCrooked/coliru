#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <boost/noncopyable.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/array.hpp>

template<typename T>
class ContainerT;

    template<typename T>
    class ContainerDataT : boost::noncopyable {
    public:
        ContainerDataT() : p_Data(new T[10]) { 
            std::copy_n("0123456789", 10, p_Data);
        }
        ~ContainerDataT() { delete[] p_Data; }

        T*  GetData(){return p_Data;};

    private:
        friend class ContainerT<T>;

        T* p_Data;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar, const unsigned int file_version) {
            ar & boost::serialization::make_array(p_Data, 10);
        }
    };

template<typename T>
class ContainerT {
public:
    const T* GetMString() const { return p_Data.GetData(); }

private:
    ContainerDataT<T> p_Data;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version) {
        ar & p_Data;
    }
};

typedef ContainerT<char> MString;

#endif /* CONTAINER_H_ */

#ifndef PERSON_H_
#define PERSON_H_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <string>

//#include "Container.h"
class Person
{
public:
     Person() = default;
    ~Person() = default;

private:    
    std::string z_Name;
    int         i_Age;
    MString     z_CountryCode;

    //Serailization
    //Allow serialization to access non-public data members.
    friend class boost::serialization::access;

    template <typename Archive> 
    void serialize(Archive &ar, const unsigned int version) 
    { 
        ar & z_Name; 
        ar & i_Age; 
        ar & z_CountryCode; 
    }   
};

#endif /* PERSON_H_ */

int main()
{
    boost::archive::text_oarchive oa(std::cout);

    Person p;
    oa << p;
}

