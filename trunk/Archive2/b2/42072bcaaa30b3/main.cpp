#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>

// just contains information about an Accountant
class Accountant
{
    private:
        std::string m_name;
        double m_salary;        // yes dealing with currency it's not good to use float types. I KNOW

    public:
        Accountant() {}
        Accountant( std::string _name, double _salary ) : m_name( _name ), m_salary( _salary ) {}
        double salary() const { return( m_salary ); }
        std::string name() const { return( m_name); }
        friend std::ostream& operator << (std::ostream &out, const Accountant &accountant);     
};

std::ostream& operator << (std::ostream &out, const Accountant &accountant)
{
    out << accountant.name() << " " << accountant.salary();
    return(out);
}

// contains a vector of Accountant and performs operations on them
class Accountants
{
    private:
        std::vector<Accountant> m_list;

    public:
        Accountants( std::vector<Accountant> list ) : m_list( std::move(list) ) {}
        friend std::ostream& operator << (std::ostream &out, const Accountants &m_list);

        // how to implement something like this?
        // 
        template<typename Callable>
        Accountants subset(Callable&& c)
        {
            std::vector<Accountant> result;
            std::copy_if(m_list.begin(), m_list.end(), std::back_inserter(result), std::forward<Callable>(c));
            return result;
        }
};

std::ostream& operator << (std::ostream &out, const Accountants &list)
{
    std::vector<Accountant>::const_iterator iter = list.m_list.begin();

    while (iter != list.m_list.end())
    {
        out << *iter << std::endl;
        ++iter; 
    }
    return(out);
}



int main(int argc, char *argv[])
{
    std::vector<Accountant> emps{{"Josh",2100.0}, {"Kate", 2900.0}, {"Rose",1700.0}};
    Accountants list( emps );

    const auto min_wage = 0.0;
    const auto upper_limit = 2900.0;

    auto lambda = ([=]( Accountant &a ){ return (a.salary() >= min_wage && a.salary() < upper_limit); });

    std::cout << "List of Accountants" << std::endl  << list << std::endl;
    std::cout << "===============================================" << std::endl;

    std::vector<Accountant>::iterator items = std::find_if(emps.begin(), emps.end(), lambda );
    while( items != emps.end() )
    {
        std::cout << (*items).name() << " " << (*items).salary() << std::endl;
        items = std::find_if(++items, emps.end(), lambda );
    }
    
    std::cout << "===============================================" << std::endl;
    // how to implement something like this?
    Accountants inRangeAccountants = list.subset( lambda );
    
    std::cout << inRangeAccountants;
}