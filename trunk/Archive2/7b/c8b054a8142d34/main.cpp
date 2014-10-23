#include <iostream>

//========================================================================
// This is Infra's log...
//========================================================================

struct InfraStupidLog 
{
private:
    bool IsInterested() const
    { 
        // Whatever here...
        return true;
    }
};

//========================================================================
// BEGIN: Black magic
//========================================================================

template<typename Tag, typename Tag::type M>
struct Spy 
{ 
    friend typename Tag::type get(Tag) { return M; }
};

struct IsInterestedRetriever
{ 
    using type = bool (InfraStupidLog::*)() const;
    
    friend type get(IsInterestedRetriever);
};

template struct Spy<IsInterestedRetriever, &InfraStupidLog::IsInterested>;

//========================================================================
// END: Black magic
//========================================================================

// Helper function...

bool IsInterested(InfraStupidLog const& log)
{
    return (log.*get(IsInterestedRetriever{}))();
}

int main() 
{
    InfraStupidLog log;
    
    // Wait for it...
    
    std::cout << IsInterested(log);
}