#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <boost/smart_ptr/shared_ptr.hpp>

class spObj
{
    int r;
public:
    spObj() : r(0) { std::cout << "spObj constructed" << std::endl; }
    spObj(const spObj &_r) : r(_r.r) { std::cout << "spObj copied" << std::endl; }
    ~spObj() { std::cout << "spObj destroyed" << std::endl; }
    spObj operator=(const spObj &_r) { this->r = _r.r; std::cout << "spObj assigned" << std::endl; return *this; }
};
//---------------------------------------------------------------------------

template<typename T>
class ItrImpl
{
private:
    typename std::vector<T>::iterator ref;
public:
    ItrImpl(typename std::vector<T>::iterator itr) : ref(itr) {};
	ItrImpl& operator++() { ++ref; return *this; };               // Next element
	spObj& operator*() { return *ref; };                  		// Dereference
	bool operator==(const ItrImpl& o) const { return ref == o.ref; };	// Comparison
	bool operator!=(const ItrImpl& o) const { return !(*this == o); }
};
//---------------------------------------------------------------------------

template<typename T>
class Itr
{
private:
	boost::shared_ptr<ItrImpl<T> > ref;
public:
//    Itr<T>(Itr<T> &itr) : ref(itr.ref.release()) {};
	Itr<T>(const ItrImpl<T> itr) : ref(new ItrImpl<T>(itr)) {};
	Itr& operator++() { ++(*ref); return *this; };                // Next element
	spObj& operator*() { return *(*ref); };                  		// Dereference
	bool operator==(const Itr& o) const { return *ref == *o.ref; };      // Comparison
	bool operator!=(const Itr& o) const { return !(*this == o); }
};
//---------------------------------------------------------------------------

typedef ItrImpl<spObj> SPItrImpl;
typedef Itr<spObj> SPItr;

class TSearchContainer
{
private:
    typename std::vector<spObj> obj_vec;
public:
    Itr<spObj> begin() { //ItrImpl<spObj> temp( obj_vec.begin() ); 
                    //Itr<spObj> temp2( temp );
                    return ItrImpl<spObj> ( obj_vec.begin() ); };
    Itr<spObj> end() { //ItrImpl<spObj> temp( obj_vec.end() ); 
                    //Itr<spObj> temp2( temp );
                    return ItrImpl<spObj> ( obj_vec.end() ); };
    unsigned int size() { return obj_vec.size(); }
    spObj push_back(const spObj &r) { obj_vec.push_back(r); return obj_vec.back(); };
    
};
//---------------------------------------------------------------------------

class TSearchModule
{
private:
    std::auto_ptr<TSearchContainer> container;
public:
	void Search(const int search_flag)
    {
        while (container->size() < (unsigned)search_flag)
        {
            spObj temp;
            container->push_back(temp);
        }
    };
	Itr<spObj> begin() { return container->begin(); };
	Itr<spObj> end() { return container->end(); };
};
//---------------------------------------------------------------------------

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
//---------------------------------------------------------------------------

int main()
{
    TSearchModule myModule;
    myModule.Search(5);
    
    struct doNothing {
    	doNothing() : row_top(0) {};
		void operator()(const spObj &obj) { ++row_top; };
		int row_top;
    };
    
    std::for_each(myModule.begin(), myModule.end(), doNothing());
}
