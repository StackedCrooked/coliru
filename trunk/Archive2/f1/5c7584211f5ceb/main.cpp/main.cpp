#include <fstream>
#include <iostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class datta {
public:
    int integers;
    float decimals;

    datta(){}
    ~datta(){}

    datta(int a, float b)   {
        integers=a;
        decimals=b;
    }

    void disp_datta()   {

        std::cout<<"\n int: "<<integers<<" float" <<decimals<<std::endl;

    }
private:
    friend class boost::serialization::access;
template<class Archive>            
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & integers;
        ar & decimals;
    }
};

int main()  {

    datta first(20,12.56);
    datta get;
    datta* point_first;
    datta* point_get;

    point_first=&first;

    first.disp_datta();
    std::cout<<"\n ptr to first :"<<point_first;

    //Serialize

    {
        std::ofstream abc("file.txt");
        boost::archive::text_oarchive def(abc);
        def << point_first;
    }

    std::cout << "\n===================================\n";
    std::ifstream zxc("file.txt");
    {
        boost::archive::text_iarchive ngh(zxc);
        ngh >> point_get;
    }

    //Dereference the ptr and

    get = *point_get;

    get.disp_datta();
    std::cout<<"\n ptr to first :"<<point_get<<"\n";
}
