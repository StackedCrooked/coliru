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
    int pName;
    vector<int> pList;

    public:
        Person(): pName(0)
        {
        }
        Person(int pName): pName(pName)
        {
        }
        ~Person()
        {
        }
        
        int getID()
        {
            return pName;
        }
        
        vector<int> getList()
        {
            return pList;
        }

        void Display()
        {
            printf("Name = %d \n", pName);
        }
        void Shout()
        {
            printf("Ooooooooooooooooo");
        } 
        Person * operator = (const Person* p)
         {
             printf("p is now my friend");
        this->pList.push_back(p->pName);
        return this;
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
    
    SP<T>&  reset ()
    {
        if(reference->Release() == 0)
        {
            delete pData;
            delete reference;
        }
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
printf("Ooooooooooooooooo\n");
            // Copy the data and reference pointer
            // and increment the reference count
            pData = sp.pData;
            reference = sp.reference;
            reference->AddRef();
        }
        return *this;
    }
    
    
    SP<T>&  add (const SP<T>& sp)
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
           // pData = sp.pData; dont change my address
           
           /* add sp to my friend list */
           
            reference = sp.reference;
            reference->AddRef();
        }
        return *this;
    }
    
};

int main()
{
    /*
    int N = 10;
    int i,j;
    vector< SP<Person> > vecp;
    for(i=0;i<N;i++)
    {
	    vecp.push_back( SP<Person>( new Person(i)));
    }
    for_each( vecp.begin(), vecp.end(),[ ](SP<Person>& p)
    		{
				p->Display();
			});
   */ 

    SP<Person> p(new Person(20));
    SP<Person> p3(new Person(23));
    p=p3;
    p->Display();
//    p.reset();
//    p.reset();
    p->Display();
//    for_each( p->getList().begin(), p->getList().end(),[ ](int x)
//        	{
//				cout<<x<<" "<<endl;
//			});
    for (int x : p->getList())
        cout << x << ' ';
     /*
    p->Display();
    {
        SP<Person> p2(new Person(22));
        SP<Person> q = p;
        
        p2->Display();
        // Destructor of q will be called here..

        SP<Person> r;
        r = p;
        r->Display();
        // Destructor of r will be called here..
    }
    p->Display();
*/
}
