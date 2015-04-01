#include <iostream>
#include <string>
#include <algorithm>    // std::for_each
#include <vector>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class Person
{
    int age;
    char* pName;

    public:
        Person(): pName(0),age(0)
        {
        }
        Person(char* pName, int age): pName(pName), age(age)
        {
        }
        ~Person()
        {
        }

        void Display()
        {
            printf("Name = %s Age = %d \n", pName, age);
        }
        void Shout()
        {
            printf("Ooooooooooooooooo");
        } 
};

class RC
{
    private:
    int count; // Reference count

    public:
    void AddRef()
    {
        // Increment the reference count
        count++;
    }

    int Release()
    {
        // Decrement the reference count and
        // return the reference count.
        return --count;
    }
};

template < typename T > class SP
{
private:
    T*    pData;       // pointer
    RC* reference; // Reference count

public:
    SP() : pData(0), reference(0) 
    {
        // Create a new reference 
        reference = new RC();
        // Increment the reference count
        reference->AddRef();
    }

    SP(T* pValue) : pData(pValue), reference(0)
    {
        // Create a new reference 
        reference = new RC();
        // Increment the reference count
        reference->AddRef();
    }

    SP(const SP<T>& sp) : pData(sp.pData), reference(sp.reference)
    {
        reference->AddRef();
    }

    ~SP()
    {
        // Destructor
        // Decrement the reference count
        // if reference become zero delete the data
        if(reference->Release() == 0)
        {
            delete pData;
            delete reference;
        }
    }

    T& operator* ()
    {
        return *pData;
    }

    T* operator-> ()
    {
        return pData;
    }
    
    SP<T>& operator = (const SP<T>& sp)
    {
        // Assignment operator
        if (this != &sp) // Avoid self assignment
        {
            // Decrement the old reference count
            // if reference become zero delete the old data
            if(reference->Release() == 0)
            {
                delete pData;
                delete reference;
            }

            // Copy the data and reference pointer
            // and increment the reference count
            pData = sp.pData;
            reference = sp.reference;
            reference->AddRef();
        }
        return *this;
    }
};

int main()
{
    
    vector< SP<Person> > vecp;
	vecp.push_back( SP<Person>( new Person("1",11) ));
	vecp.push_back( SP<Person>( new Person("2",22) ));
    
    for_each( vecp.begin(), vecp.end(),[ ](SP<Person>& p)
    		{
				p->Display();
			});
    
/*
    SP<Person> p(new Person("Scott", 25));
    p->Display();
    {
        SP<Person> q = p;
        q->Display();
        // Destructor of q will be called here..

        SP<Person> r;
        r = p;
        r->Display();
        // Destructor of r will be called here..
    }
    p->Display();
*/
}
