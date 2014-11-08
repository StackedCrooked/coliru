#include <iostream>
#include <string>
#include <vector>
#include <list>

class myDestructorClass
{
private:
    static int theCount;

public:
	myDestructorClass()
	{}

	~myDestructorClass()
	{
		++theCount;
		std::cout << theCount << " objects deleted\n";
	}

	friend void swap(myDestructorClass& first, myDestructorClass& second)
	{
		using std::swap;
		//don't swap theCount because it is static
	}

	myDestructorClass& operator=(myDestructorClass that)
	{
		swap(*this, that);
		return *this;
	}
};

int myDestructorClass::theCount = 0;

template<class T> class myContDestr
{
private:
    T *OwnedPtrs_container;

	myContDestr& operator=(myContDestr that);	//assignment is undesirable--make it uncallable
	myContDestr(const myContDestr &that);	//copy construction is undesirable--make it uncallable
public:
	myContDestr(T &cont_ptrs_to_own) : OwnedPtrs_container(&cont_ptrs_to_own)
	{}

	~myContDestr()
	{
		if(OwnedPtrs_container)
		{
			for(typename T::iterator del_itr = OwnedPtrs_container->begin();
				del_itr != OwnedPtrs_container->end();
				++del_itr)
            {
				if( *del_itr )
					delete (*del_itr);
            }
		}
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<myDestructorClass *> ptr_vec;
    std::list<myDestructorClass *> ptr_list;

	myContDestr<std::vector<myDestructorClass *> > VecPtrOwner(ptr_vec);
    myContDestr<std::list<myDestructorClass *> > ListPtrOwner(ptr_list);
    
    ptr_vec.push_back(new myDestructorClass());
    ptr_vec.push_back(new myDestructorClass());
    ptr_vec.push_back(new myDestructorClass());
    ptr_vec.push_back(new myDestructorClass());
    ptr_vec.push_back(new myDestructorClass());
    
    ptr_list.push_back(new myDestructorClass());
    ptr_list.push_back(new myDestructorClass());
    ptr_list.push_back(new myDestructorClass());
    ptr_list.push_back(new myDestructorClass());
    ptr_list.push_back(new myDestructorClass());
}
