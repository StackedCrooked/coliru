#include <iostream>
#include <string>

class tire
{
    protected:
        std::string make; // http://www.mochima.com/tutorials/strings.html
        double cost, price;
        int size;

    public:
        tire( const char* mk, double cst, int size ) : make(mk), cost(cst), size(size)
        { price = cost * 1.06 ; }

        // virtual void set_price() { price = cost * 1.06;}

        // http://www.parashift.com/c++-faq-lite/const-member-fns.html
        virtual double get_price() const { return price;}
        virtual std::string get_make() const { return make;}
        virtual int get_size() const {return size;}
};

// http://www.parashift.com/c++-faq-lite/overview-const.html
std::ostream& operator<<( std::ostream& os, const tire& x )
{
    os << x.get_make() << " (price:" << x.get_price() << ")\n";
    return os;
}

class winter_tire: public tire
{
    private:
        double mounting_cost;

    public:
        winter_tire( int sz, const char* mk, double cst = 165.00, double mntg_cst = 26.00 ) : tire( mk, cst, sz )
        {
            mounting_cost = mntg_cst;
            price = mounting_cost + ( 1.04 * cost );
        }
};

int main()
{
    tire gangster( "hey", 10.00, 5 );
    std::cout << gangster << '\n' ;

    winter_tire gangster2( 5, "hey2", 10.00 );
    std::cout << gangster2 << '\n' ;
}
