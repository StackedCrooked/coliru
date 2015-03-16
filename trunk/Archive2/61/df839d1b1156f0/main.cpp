#include <iostream>
#include <vector>
#include <map>
using namespace std;


typedef vector<int> PrefList;
typedef map<int, PrefList> PrefMap;
typedef multimap<int, int> Matching;

Matching RVV(Matching Matched);
Matching stable(Matching m,PrefMap PrefCHLists,PrefMap PrefONLists);
void add(int a, std::string state, std::map<int,int> &S, Matching &m, Matching &BPlist);
void satisfy(int CH,int ON, std::map<int,int> &S, Matching &m);
bool blockingAgent(int bA, std::map<int,int> S, Matching m);

map<int, int> CHcapacity ={{1,1},{2,1},{3,1}};
PrefMap PrefCHLists = {{1,{5,4,6}},{2,{4,6,5}},{3,{4,5,6}}};
PrefMap PrefONLists = {{4,{2,1,3}},{5,{3,1,2}},{6,{1,3,2}}};
int main()
{
    Matching match={{1,4},{2,5},{3,6}};
    Matching final=RVV(match);
    cout<<final.size()<<"\n";
    for( Matching::iterator it = final.begin(); it != final.end(); it++ ){
        cout<<it->first<<"->"<<it->second<<"\n";
    }
}

Matching RVV(Matching m){
    Matching tempMatch=m;
    map<int, int> S;
    Matching BP = stable(tempMatch, PrefCHLists, PrefONLists);
    while (BP.size() > 0){
        bool addB = false;
        for( Matching::iterator it = BP.begin(); it != BP.end(); it++ ){
            if(S.find(it->first)!= S.end() && S.find(it->second)== S.end()){
                add(it->first,"CH", S, tempMatch, BP);
                addB = true;
                break;
            }else
            if(S.find(it->second)!= S.end() && S.find(it->first)== S.end()){
                add(it->second,"ON", S, tempMatch, BP);
                addB = true;
                break;
            }
        }
        if(!addB){
            satisfy(BP.begin()->first,BP.begin()->second, S, tempMatch); //soddisfo sempre la prima???
        }
        cout<<"a";
        BP.clear();
        //BP = stable(tempMatch, PrefCHLists, PrefONLists);
    }
    return tempMatch;
}

Matching stable(Matching m,PrefMap PrefCHLists,PrefMap PrefONLists){
    Matching BP;
    for(auto const& p : PrefCHLists){
        const int CH = p.first;
        const PrefList CHpref = p.second;
        std::pair <Matching::iterator, Matching::iterator> ret;
        ret = m.equal_range(CH);
        PrefList ONmatched;
        for( Matching::iterator it = ret.first; it != ret.second; it++ ){
            ONmatched.push_back(it->second);
        }
        size_t j = 0;
        for( int i = 0; i < CHcapacity[CH]; i++ ){
            if(j < CHpref.size()){
                const int ON = CHpref[j];
                bool found = false;
                for( size_t k = 0; k < ONmatched.size(); k++ ){
                    if( ON == ONmatched[k] ){
                        found=true;
                        break;
                    }
                }
                if(found==false){
                    bool insertBP = true;
                    for( Matching::iterator it = m.begin(); it != m.end(); it++ ){
                        if(it->second == ON){
                            const int onCH = it->first;
                            PrefList ONpref = PrefONLists.find(ON)->second;
                            for(size_t iter = 0; iter < ONpref.size(); iter++){
                                if(ONpref[iter]==CH){
                                    break;
                                }
                                if(ONpref[iter]==onCH){
                                    insertBP = false;
                                    i--;
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    if(insertBP){
                        BP.insert(std::pair<int, int>(CH,ON));
                        //devo uscire appena trovo una blocking pair del CH???
                        break;
                    }
                }
                j++;
            }
        }
    }
    return BP;
}

void add(int a, std::string state, std::map<int,int> &S, Matching &m, Matching &BPlist){
    if(state=="ON"){
        for( Matching::iterator it = m.begin(); it != m.end(); it++ ){
            if(it->second == a){
                m.erase(it);
                break;
            }
        }
        S[a]=1;
        while(blockingAgent(a, S, m)){
            int worstON;
            int bestCH;
            const PrefList ONpref = PrefONLists[a];
            for(size_t it=0; it<ONpref.size(); it++){
                if(S.find(ONpref[it])==S.end()){
                    bestCH=ONpref[it];
                    break;
                }
            }
            if(m.count(bestCH)>=CHcapacity[bestCH]){
                Matching::iterator worst;
                int iWorst=-1;
                std::pair <Matching::iterator, Matching::iterator> ret;
                ret = m.equal_range(bestCH);
                PrefList CHpref = PrefCHLists.find(bestCH)->second;
                for( Matching::iterator it = ret.first; it!=ret.second; it++ ){
                    const int tON = it->second;
                    for(size_t jt = 0; jt < CHpref.size(); jt++){
                        if(CHpref[jt] == tON){
                            if(iWorst < jt){
                                iWorst = jt;
                                worst = it;
                                break;
                            }
                        }
                    }
                    if(iWorst==-1){
                        worst = it;
                        iWorst = CHpref.size();
                        break;
                    }
                }
                worstON = worst->second;
                m.erase(worst);
            }
            m.insert(std::pair<int,int>(bestCH, a));
            a = worstON;
        }

    }else if(state=="CH"){
        if(m.count(a)>=CHcapacity[a]){
            Matching::iterator worst;
            int iWorst=-1;
            std::pair <Matching::iterator, Matching::iterator> ret;
            ret = m.equal_range(a);
            PrefList CHpref = PrefCHLists.find(a)->second;
            for( Matching::iterator it = ret.first; it!=ret.second; it++ ){
                const int tON = it->second;
                for(size_t jt = 0; jt < CHpref.size(); jt++){
                    if(CHpref[jt] == tON){
                        if(iWorst < jt){
                            iWorst = jt;
                            worst = it;
                            break;
                        }
                    }
                }
                if(iWorst==-1){
                    worst = it;
                    iWorst = CHpref.size();
                    break;
                }
            }
            m.erase(worst);
        }
        S[a]=1;
        while(blockingAgent(a, S, m)){
            int wCH;
            int bestON;
            const PrefList CHpref = PrefCHLists[a];
            for(size_t it=0; it<CHpref.size(); it++){
                if(S.find(CHpref[it])==S.end()){
                    bestON=CHpref[it];
                    break;
                }
            }
            for( Matching::iterator it = m.begin(); it != m.end(); it++ ){
                if(it->second == bestON){
                    wCH=it->first;
                    m.erase(it);
                    break;
                }
            }
            m.insert(std::pair<int,int>(a, bestON));
            a = wCH;
        }
    }

}

void satisfy(int CH,int ON, std::map<int,int> &S, Matching &m){
    S[ON]=1;
    S[CH]=1;
    for( Matching::iterator it = m.begin(); it != m.end(); it++ ){
       if(it->second == ON){
           m.erase(it);
           break;
       }
    }
    if(m.count(CH)>=CHcapacity[CH]){
        Matching::iterator worst;
        int iWorst=-1;
        std::pair <Matching::iterator, Matching::iterator> ret;
        ret = m.equal_range(CH);
        PrefList CHpref = PrefCHLists.find(CH)->second;
        for( Matching::iterator it = ret.first; it!=ret.second; it++ ){
            const int tON = it->second;
            for(size_t jt = 0; jt < CHpref.size(); jt++){
                if(CHpref[jt] == tON){
                    if(iWorst < jt){
                        iWorst = jt;
                        worst = it;
                        break;
                    }
                }
            }
            if(iWorst==-1){
                worst = it;
                iWorst = CHpref.size();
                break;
            }
        }
        m.erase(worst);
    }
    m.insert(std::pair<int,int>(CH, ON));
}

bool blockingAgent(int bA, std::map<int,int> S, Matching m){
    std::vector<Matching::iterator> dCanc;
    for( Matching::iterator it = m.begin(); it!=m.end(); it++){
        if(S.find(it->first)!=S.end() || S.find(it->second)!=S.end()){
            dCanc.push_back(it);
        }
    }
    for(size_t i=0; i<dCanc.size(); i++){
        m.erase(dCanc[i]);
    }
    PrefMap tPrefCHLists=PrefCHLists;
    PrefMap tPrefONLists=PrefONLists;
    for( Matching::iterator it = S.begin(); it!=S.end(); it++){
        PrefMap::iterator canc=tPrefCHLists.find(it->first);
        if(canc!=tPrefCHLists.end()){
            tPrefCHLists.erase(canc);
        }
        canc=tPrefONLists.find(it->first);
        if(canc!=tPrefONLists.end()){
            tPrefONLists.erase(canc);
        }
    }
    Matching BP = stable(m, tPrefCHLists, tPrefONLists);
    if (BP.size() > 0){
        for(Matching::iterator it = BP.begin(); it!=BP.end(); it++){
            if(it->first==bA || it->second==bA ){
                return true;
            }
        }
    }
    return false;
}