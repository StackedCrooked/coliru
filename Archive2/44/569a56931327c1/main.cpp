#include <iostream>
#include <string>
#include <algorithm>    // std::for_each
#include <list>

using namespace std;

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
    
    T& operator* () const
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
            // Copy the data and reference pointer
            // and increment the reference count
            pData = sp.pData;
            reference = sp.reference;
            reference->AddRef();
        }
        return *this;
    }
    
    bool operator==(const SP<T>& sp) const
    {
        return this->pData == sp.pData;
    }
};

class Person
{
    public:
        Person();
        Person(Person &&);
        Person(const Person&) = delete;
        ~Person();
        
        bool isFriend(const Person &p) const;
        
        //add friend
        void addFriend(Person &p);
        
        //remove friend from friend list, randomly selected
        void unFriend();
        
        //return true if this person has no friend
        bool noFriend() const;
        
        //remove friends that no longer exist
        void clearFriends();
        
//        int getID(){ return pName;}

//        void Display(){printf("Name = %d \n", pName);}

    private:
//        int pName;
        SP<int> follower; /***to be decided****/
        list<SP<int>> following;
};

Person::Person():follower { new int}
{
    *follower = 1;   
}

Person::Person(Person &&b) :
    follower {move(b.follower)},
    following {move(b.following)}
{} 

Person::~Person()
{
    if(follower==NULL)
        *follower = 0;  // 0 means this person is no longer in the social network
}

bool Person::isFriend(const Person &p) const
{
    for (auto it = following.cbegin(); it != following.cend(); ++it) {
        if (*it == p.follower)
            return true;
    }
    return false; 
}

void Person::addFriend(Person &p)
{
    following.push_back(SP<int>(p.follower));
}

void Person::unFriend()
{
    ///???????????????????
    mt19937 seed;
    if (!following.empty()) {
        uniform_int_distribution<> dis(0, following.size() - 1);
        auto unfriend = following.begin();
        for(int pos = dis(seed); pos > 0; --pos, ++unfriend);
        following.erase(unfriend);
    }        
}

bool Person::noFriend() const
{
    return following.empty() || *follower == 0;    
}

void Person::clearFriends()
{
    following.remove_if([](SP<int> &p){ return *p == 0; });
}

int main()
{
   int init_population = 5;
   int iterations = 100;
   random_device rd;
   mt19937 gen(rd());
   uniform_int_distribution<> dis(1, 3);
   list<Person> network;
   
   
   //add initial persons into the network
    for (int i = 0; i < init_population; ++i) {
        network.push_back(Person());
    }
    
    //let initial persons be friends with each other
    for (auto it = network.begin(); it != network.end(); ++it) {
        for (auto it2 = network.begin(); it2 != network.end(); ++it2) {
            if (it == it2) continue; //avoid adding oneself as friend
            it->addFriend(*it2);
            it2->addFriend(*it);
        }
    }    
    
    //iterate
    for (int i = 0; i < iterations; ++i) {
        for (auto it = network.begin(); it != network.end(); ++it) {
            switch (dis(gen)) {
            case 1:
//                cout<<"case 1"<<endl;
                it->unFriend();
                break;
            case 2:
//            cout<<"case 2"<<endl;
                it->unFriend();
                for (auto newfriend = network.begin(); newfriend != network.end(); ++newfriend) {
                    if (newfriend == it)   continue;//aviod adding the person back who just unfollowed
                    if (!it->isFriend(*newfriend)) {
                        it->addFriend(*newfriend);
                        break;
                    }
                }
                break;
            case 3:
//            cout<<"case 3"<<endl;
                network.push_back(Person());
                it->addFriend(network.back());
                network.back().addFriend(*it);
                break;
            }
        }
        
        // remove people who have no friends from network
        network.remove_if([](const Person& p){ return p.noFriend(); });
        
        // clear the friend list for each person. In these friend lists, persons that are no longer in the network is removed.
        for (auto it = network.begin(); it != network.end(); ++it) {
            it->clearFriends();
        }
    }
    
    cout << "There are " << network.size() << " persons in the network after "<<iterations<<" iterations."<<endl;
}
