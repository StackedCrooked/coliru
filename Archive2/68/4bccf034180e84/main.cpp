#include <algorithm>
#include <vector>

struct Session
{
    Session& operator=(const Session&) = delete;
    Session& operator=(Session&&) = default;
};

int main()
{
    std::vector<Session> sessions;
    
    std::remove_if(sessions.begin(), sessions.end(), 
        [] (Session const&) {
            return false;
        });
}
