#include <iostream>
#include <string>
#include <vector>
#include <map>

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

class ThingNoMove
{
    public:
    ThingNoMove(const std::string& name)
        : mName(name)
    {
        cout << "ctor  - " << mName << endl; 
    }
    
    ThingNoMove(const ThingNoMove& other)      
    {
        cout << "copy ctor  [" << mName << " -> " << other.mName << "]" << endl; 
        mName = other.mName;
    }
    
    ThingNoMove& operator=(const ThingNoMove& other) 
    {
        cout << "copy assign [" << mName << " -> " << other.mName << "]" << endl; 
        mName = other.mName;
        return *this;
    }
    ~ThingNoMove() 
    {
        cout << "dtor - " << mName << endl;
    }
    std::string mName;
};

class Thing
{
    public:
    Thing(const std::string& name, unsigned int size) 
        : mName(name)
        , mSize(size)
        , mImportantData(new int[size])
    {   
        cout << "ctor  - " << mName << "[" << mSize << "]"<< endl; 
    }
    Thing(const Thing& other)       
    {
        cout << "copy ctor  [" << mName << " -> " << other.mName << "][" << other.mSize << "]" << endl; 
        mName = other.mName;
        mSize = other.mSize;
        mImportantData = new int[other.mSize];
        //copy other.mImportantData to mImportantData;
    }
    Thing& operator=(const Thing& other)  
    {
        cout << "copy assign [" << mName << " -> " << other.mName << "] [" << other.mSize << "]" << endl; 
        mName = other.mName;
        mSize = other.mSize;
        mImportantData = new int[other.mSize];
        //copy other.mImportantData to mImportantData;
        return *this;
    }
    
    //if we really move all the members then no new resource
    //created, so no exception should raise.
    //parameter can not be const, noexpect needed
    Thing(Thing&& other) noexcept   
    {
        cout << "move ctor  [" << mName << " -> " << other.mName << "] [" << other.mSize << "]" << endl;
        mName = other.mName; 
        mSize = other.mSize;
        mImportantData = other.mImportantData; //pointer copy, what????
        other.mImportantData = nullptr;        //because we remove access to the heap in the other object
        other.mName = "[killed: "+other.mName+"]"; 
    }
    
    Thing& operator=(Thing&& other) 
    {
        cout << "move assign [" << mName << " -> " << other.mName << "] [" << other.mSize << "]" << endl; 
        mName = other.mName; 
        mImportantData = other.mImportantData; //pointer copy, what????
        other.mImportantData = nullptr;     //because we remove access to the heap in the other object
        other.mName = "[killed: "+other.mName+"]"; 
        return *this;
    }
    
    ~Thing() 
    {
        cout << "dtor - " << mName << endl;
        delete [] mImportantData;
    }
    
    std::string mName;
    int  mSize;
    int* mImportantData;
};

ThingNoMove returnObject_standard()
{
    ThingNoMove a("return object_standard");
    return a;
}

ThingNoMove returnObject_move()
{
    ThingNoMove a("return object_move");
    return std::move(a);    //this is a best effor function.
}

Thing returnObject2_standard()
{
    Thing a("return object2_standard", 7);
    return a;
}

Thing returnObject2_move()
{
    Thing a("return object2_move", 9);
    return std::move(a);
}

int main()
{
    cout << ">>>only copy ctor & assign<<<" <<endl;
    {
        ThingNoMove a("ThingNoMove1");
        ThingNoMove b = a;
        ThingNoMove c("Temporary");
        c = a;
        // ThingNoMove c = move(a);    //ERROR: move const is deleted
        // b = move(a);                //ERROR: move assignment is deleted
    }
    cout << "---------------------------------------" <<endl;
    cout << ">>>move operators and normal usage<<<" <<endl;
    {
        Thing a("Thing - normal", 11);
        Thing b = a;
        b = a;
        cout << ">>>end of scope" <<endl;
    }
    cout << "---------------------------------------" <<endl;
    cout << ">>>move operators and std::move<<<" <<endl;
    {
        Thing a("Thing - move", 11);
        Thing b = move(a);
        cout << "a is moved and lost its identity: " << a.mName << endl;
        Thing c("Thing2", 34);
        c = move(b); // b contains all the data from a.
        cout << ">>>end of scope" <<endl;
    }
    cout << endl << "---------------------------------------" <<endl;
    cout << ">>>return object from function<<<"<< endl;
    {
        cout << "--- return with copy - no move operations ---" << endl;
        ThingNoMove a = returnObject_standard();        //only one ctor => Return Value Optimization(RVO), object created in-place without function call
        cout << "now without RVO:" <<endl;
        ThingNoMove b("temporary1");
        b = returnObject_standard();                    //no RVO, ctor in function, copy assign to g, dtor for temporary.
        cout << "--- return with move - no move operations --- " << endl;
        ThingNoMove c = returnObject_move();            //RVO does not work with forced move, and does not move as no move operations
        cout << "now without RVO:" <<endl;
        ThingNoMove d("temporary2");
        d = returnObject_move();
        cout << ">>>end of scope" <<endl;
    }
    cout << endl << "---------------------------------------" <<endl;
    {
        cout << "--- return with move - has move operations ---" << endl;
        Thing a = returnObject2_standard();              //ctor in function, move to f, dtor to temporary.
        Thing b("temporary1", 2);
        b =  returnObject2_standard();
        cout << "move assign:" << endl;
        Thing c = returnObject2_move();
        Thing d("temporary2", 3);
        d = returnObject2_move();
        cout << ">>>end of scope" <<endl;
    }
    cout << "---------------------------------------" <<endl;
    cout << ">>>end of program<<<" << endl;
}
