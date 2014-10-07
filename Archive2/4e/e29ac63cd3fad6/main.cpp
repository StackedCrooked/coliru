#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class A
{
    public:
        A(){};
        A(std::string name):name_(name){}
        virtual ~A(){}
 
        std::string name(){ return name_; };
 
        virtual std::string description(){ return name_; }
 
    private:
 
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar,const unsigned int version)
        {
             ar & name_;
        }
 
        std::string name_;
};
 
class B: public A
{
    public:
        B():A(){}
        B(std::string name,int intValue)
             :A(name),
             intValue_(intValue)
        {}
 
        std::string description()
        {
         std::stringstream ss;
         ss<< name() <<" "<<intValue_;
         return ss.str();
        }
 
        int intValue(){ return intValue_; }
 
    private:
 
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar,const unsigned int version)
        {
             ar & boost::serialization::base_object<A>(*this);
             ar & intValue_;
        }
 
        int intValue_;
};
 
 
class C: public A
{
    public:
        C():A(){}
        C(std::string name,double doubleValue)
         : A(name),
             doubleValue_(doubleValue)
        {}
 
        std::string description()
        {
            std::stringstream ss;
            ss<< name() <<" "<<doubleValue_;
            return ss.str();
        }
 
        double doubleValue(){ return doubleValue_; }
 
    private:
 
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive &ar,const unsigned int version)
        {
             ar & boost::serialization::base_object<A>(*this);
             ar & doubleValue_;
        }
 
        double doubleValue_;
};

std::stringstream ss;
 
void save()
{
    boost::archive::text_oarchive oa(ss);
 
    //oa.register_type<A>();  //???
    oa.register_type<B>();
    oa.register_type<C>();
 
    A* a= new A("A1");
    oa<<a;
 
    A* b= new B("B1",10);
    oa<<b;
 
    A* c= new C("C1",3.14);
    oa<<c;
    
    delete a;
    delete b;
    delete c;
}
 
void load()
{
    boost::archive::text_iarchive ia(ss);
 
    //ia.register_type<A>();  //???
    ia.register_type<B>();
    ia.register_type<C>();
 
    A* a;
    ia>>a;
    std::cout<< a->description()<<std::endl;
    delete a;
 
    B* b;
    ia>>b;
    std::cout<< b->description()<<std::endl;
    delete b;
 
    C* c;
    ia>>c;
    std::cout<< c->description()<<std::endl;
    delete c;
}
 
int main()
{
    save();
    load();
    return 0;
}