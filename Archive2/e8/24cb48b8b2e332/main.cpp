#include <vector>
#include <mutex>
#include <memory>
#include <deque>
#include <algorithm>

using LockGuard = std::lock_guard<std::mutex>;
std::mutex historyMutex;

struct ProtocolMessage { //stub
    int GetPlayerDest() const { return 1; }
    int GetPid()        const { return 1; }
    int GetMid()        const { return 1; }
};

struct MessageFilter {
    virtual bool messageIsOk(int)  const { return true; }
    virtual ~MessageFilter() { }
};

struct MessageHistory 
{
    using PM = std::shared_ptr<ProtocolMessage>;

    struct Query {
        bool allPlayers;
        int playerId;
        MessageFilter *filter;

        Query(bool allPlayers = true, int playerId = -1, MessageFilter* filter = nullptr) :
            allPlayers(allPlayers), playerId(playerId), filter(filter)
        {
        }

        bool operator()(PM const& pm) const {
            if (!(pm->GetPid() && pm->GetMid()))
                return false;

            int  pmtype = (pm->GetPid() << 16) + pm->GetMid();
            bool pmok   = !filter || filter->messageIsOk(pmtype);

            int  uid         = pm->GetPlayerDest();
            bool matchPlayer = uid == -1 || allPlayers || (playerId != -1 && uid == playerId);
            
            return pmok && matchPlayer;
        }
    };

    bool getMessages(std::vector<PM> &v, Query const& query)
    {
        LockGuard lock(historyMutex);

        v.clear();
        std::copy_if(historyQueue.begin(), historyQueue.end(), back_inserter(v), query);

        return true;
    }

  private:
    std::deque<PM> historyQueue;
};

int main() {
    MessageHistory hist;

    std::vector<MessageHistory::PM> v;
    hist.getMessages(v, MessageHistory::Query { false, 42 }); // only uid 42; no MessageFilter
}
