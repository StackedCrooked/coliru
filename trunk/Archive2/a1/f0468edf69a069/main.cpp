#include <iostream>

//========================================================================
// This is Infra's log...
//========================================================================

struct InfraStupidLog 
{
private:
    bool IsInterested() const
    { 
        auto result = true;
        std::cout << "Let's return " << result << std::endl; 
        return result; 
    }
};

//========================================================================
// Black magic (begin)
//========================================================================

template<typename Tag, typename Tag::type M>
struct Spy 
{ 
    friend typename Tag::type get(Tag) 
    {
        return M;
    }
};

struct IsInterestedRetriever
{ 
    using type = bool(InfraStupidLog::*)() const;
    
    friend type get(IsInterestedRetriever);
};

template struct Spy<IsInterestedRetriever, &InfraStupidLog::IsInterested>;

//========================================================================
// Black magic (end)
//========================================================================

// Helper function...
void IsInterested(InfraStupidLog const& log)
{
    (log.*get(IsInterestedRetriever{}))();
}

int main() 
{
    InfraStupidLog log;
    
    IsInterested(log); // Voila!
}