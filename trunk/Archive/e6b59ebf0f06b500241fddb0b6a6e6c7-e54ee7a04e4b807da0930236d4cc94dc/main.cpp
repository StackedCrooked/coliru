#include<iostream>

class deg
{
public:
    enum degtype{cel,fah};

    void set(double v){_val=v;}
    void add(double v){_val+=v;}
    double  val()const{return _val;}
    degtype type()const{return _type;}
    const char* typeString()const;
    friend std::ostream& operator<<(std::ostream& os,const deg& d);

    void transform(const deg& in);
protected:
    deg(double v=0.0):_val(v){}
    void settype(degtype t){_type=t;}
private:
    double cfin(const deg& d);
    double cfout(deg::degtype type,double cfval)const;
    void setcfval(double cfval);

    degtype _type;
    double  _val;
};
const char* deg::typeString()const
{
    if (_type==cel) return "C";
    if (_type==fah) return "F";
    return "(non)";
}
std::ostream& operator<<(std::ostream& os,const deg& d)
{
    os << d.val() << d.typeString();
    return os;
}
class celsius:public deg
{
public:
    celsius(double v=0.0):deg(v){settype(cel);};
};
class fahrenheit:public deg
{
public:
    fahrenheit(double v=0.0):deg(v){settype(fah);};
};
double deg::cfin(const deg& d)
{

    //std::cout<<"cfin()"<<d<<"\n";
    double cfval=0;
    switch (d.type())
    {
        case deg::cel:
            cfval=d.val();
            break;
        case deg::fah:
            cfval=(d.val()-32.0)/9.0*5.0;
            break;
        default:
            std::cerr << "deg::cfin() type error\n";
            break;
    }

    return cfval;
}
double deg::cfout(deg::degtype type,double cfval)const
{
    //std::cout<<"cfout()"<<typeString()<<"\n";
    double val=0;
    switch (type)
    {
        case deg::cel:
            val=cfval;
            break;
        case deg::fah:
            val=cfval/5.0*9.0+32.0;
            break;
        default:
            std::cerr << "deg::cfout() type error\n";
            break;
    }

    return val;
}
void deg::setcfval(double cfval)
{
    set(cfout(_type,cfval));
}
void deg::transform(const deg& in)
{
    setcfval(cfin(in));
}
int main()
{
    celsius    c;
    fahrenheit f;
    for(c.set(25.0);c.val()<37.0;c.add(0.5))
    {
        f.transform(c);
        std::cout<<c<<"\t\t"<<f<<"\n";
    }
    return 0;
}