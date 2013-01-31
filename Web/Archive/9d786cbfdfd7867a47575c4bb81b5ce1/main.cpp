#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <initializer_list>

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
    StringHolder(StringHolder && moveFrom) noexcept
     : myStr(std::move(moveFrom.myStr))
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
    StringHolder& operator=(StringHolder&& moveFrom) noexcept
    {
        // Make sure we are not assigning to ourself
        if (this != &moveFrom)
        {
            // Move-assign myStr (we invoke it via operator= just so we're clear on the std::forward() definition
            myStr.operator=(std::move(moveFrom.myStr));

            std::cout << "StringHolder operator=(MOVE) called, now owning: " << myStr << std::endl;
        }
        return *this;
    }
};


// Proxy initializer_list functions
template <typename Container, typename Iterator, typename LType>
void insertInitListProxy(Container & Cnt, Iterator pos, std::initializer_list<LType> il)
{
    for (auto it = il.begin(); it < il.end(); ++it)
    {
        pos = Cnt.emplace(pos, *it);
        ++pos;  // move to position *after* what was just inserted
    }
}

template <typename VecT, typename Iterator, typename LType>
void insertInitListProxy(std::vector<VecT> & Cnt, Iterator pos, std::initializer_list<LType> il)
{
    // save iterator 'distance' from begin() in case a resize operation happens
    auto diff = pos - Cnt.begin();
    // pre-allocate space
    Cnt.reserve(Cnt.size() + il.size());
    // reset iterator based on any changes that occurred due to a resize
    // from here on out, we don't need to worry about resizes
    pos = Cnt.begin() + diff;
    // construct the items in-place
    for (auto it = il.begin(); it < il.end(); ++it)
    {
        pos = Cnt.emplace(pos, *it);
        ++pos;  // move to position *after* what was just inserted
    }
}


int main ()
{
    std::vector<StringHolder> myVec;

    // Reserve some space so no vector resizing takes place
    myVec.reserve(20);

    std::cout << "---------- Pushing data on vector ----------\n" << std::endl;

    myVec.push_back("charstr");

    std::cout << "\n------ Now invoking initializer_list insertion ------\n" << std::endl;

    myVec.insert(myVec.end(), {"str1", "str2"});

    std::cout << "\n------ Now invoking initializer_list proxy ------\n" << std::endl;

    insertInitListProxy(myVec, myVec.end(), {"str3", "str4", "str5"});

    std::cout << "\n---------- Vector Destruction looming ----------\n" << std::endl;

    return 0;
}
