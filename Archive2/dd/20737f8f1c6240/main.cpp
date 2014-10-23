#include <iostream>

//========================================================================
// This is Infra's log...
//========================================================================

struct InfraLog 
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
    using type = bool (InfraLog::*)() const;
    
    friend type get(IsInterestedRetriever);
};

template struct Spy<IsInterestedRetriever, &InfraLog::IsInterested>;

//========================================================================
// END: Black magic
//========================================================================

// Helper function...

bool IsInterested(InfraLog const& log)
{
    return (log.*get(IsInterestedRetriever{}))();
}

int main() 
{
    InfraLog log;
    
    // Wait for it...
    
    std::cout << IsInterested(log);
}