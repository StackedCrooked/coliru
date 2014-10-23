#include <set>
#include <string>

struct NPC {
    std::string name;
    bool operator<(NPC const & other) const { return other.name > name; }
};

int main() {
    std::set<NPC> TestSet;
    for(int n = 0; n != 50; n++)
    {
        NPC npc;
        TestSet.insert(npc);
    }
    clock_t sCreation = clock();
    int sJohns = 0;
    std::set<NPC>::iterator it;
    for(it = TestSet.begin(); it != TestSet.end(); it++)
    {
        if(it->name == "John")
        {
            sJohns++;
        }
    }
    clock_t sFinished = clock();
}
