#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <initializer_list>
#include <type_traits>

// A simple (incomplete) wrapper for string objects which is used to demonstrate
// how initializer_lists work with objects
class StringHolder{
protected:
    std::string myStr;
public:
    StringHolder() : myStr()
        { std::cout << "StringHolder empty constructor" << std::endl; }
    StringHolder(const char* sInit) : myStr(sInit)
        { std::cout << "StringHolder(const char*) constructor, init string: " << sInit << std::endl; }
    // Copy-construct
    StringHolder(const StringHolder & copyFrom) : myStr(copyFrom.myStr)
        { std::cout << "StringHolder (*COPY*) Constructor called, made COPY of: " << myStr << std::endl; }
    // Move-construct
    StringHolder(StringHolder && moveFrom)
     : myStr(std::forward<std::string>(moveFrom.myStr))
    {
        // Note we already move-constructed string myStr, which has its own move constructor
        std::cout << "StringHolder (*MOVE*) Constructor called, now owning: " << myStr << std::endl;
    }
    ~StringHolder()
    { std::cout << "~StringHolder ~destructor~, string contents: " << myStr << std::endl; }
    
    // Copy-Assignment
    StringHolder& operator=(const StringHolder& copyFrom)
    {
        // Make sure we are not assigning to ourself
        if (this != &copyFrom)
        {
            /* Clear our values, release resources */
            myStr.clear();
            /* Copy in new values/resources */
            myStr = copyFrom.myStr;

            std::cout << "StringHolder operator=(COPY) called, made COPY of: " << myStr << std::endl;
        }
        return *this;
    }
    // Move-Assignment
    StringHolder& operator=(StringHolder&& moveFrom)
    {
        // Make sure we are not assigning to ourself
        if (this != &moveFrom)
        {
            // Move-assign myStr (we invoke it via operator= just so we're clear on the std::forward() definition
            myStr.operator=(std::forward<std::string>(moveFrom.myStr));

            std::cout << "StringHolder operator=(MOVE) called, now owning: " << myStr << std::endl;
        }
        return *this;
    }
};


// initializer_list Proxy - Using Insert Iterators
template <typename InsIter, typename LType>
void insertInitListProxy(InsIter inserter, std::initializer_list<LType> il)
{
    // construct & move the items into the container
    for (auto it = il.begin(); it < il.end(); ++it)
    	*inserter++ = *it;
}


int main ()
{
    std::vector<StringHolder> myVec;
    
    // Reserve some space so no vector resizing takes place
    myVec.reserve(20);
    
    // Create a back_insert_iterator for our vector
    std::back_insert_iterator<std::vector<StringHolder>> myIns(myVec);
    
    std::cout << "---------- Pushing data on vector ----------\n" << std::endl;
    
    // Traditional method of adding data
    *myIns++ = "strA";
    *myIns++ = "strB";
    
    // Alternate means of adding data - do NOT use in your code!
    //  (only meant to demonstrate what happens)
    myIns= "strC"; // calls push_back()
    myIns= "strD"; // and again

    std::cout << "\n------ Now invoking initializer_list insertion ------\n" << std::endl;

    myVec.insert(myVec.end(), {"str1", "str2"});

    std::cout << "\n------ Now invoking initializer_list proxy ------\n" << std::endl;

    // Here we could pre-allocate the needed space before the call,
    // though it's not very intuitive:
    //myVec.reserve(myVec.size() + 3);

    // insert_iterator version of the 'other' initializer_list Proxy:
    insertInitListProxy(std::back_inserter(myVec), {"str3", "str4", "str5"});

    std::cout << "\n---------- Vector Destruction looming ----------\n" << std::endl;

    return 0;
}
