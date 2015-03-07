#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <future>
using namespace std;

struct State {
    int action;
    vector<int> in;
    vector<int> out;
    
    atomic<bool> flagIn;
    atomic<bool> flagOut;
};

void DFS(vector<State> & app, int id, bool out) {
    auto & state = app[id];
    
    if(out) {
        if(state.flagOut) {
            return;
        }
        state.flagOut = true;
        
        for(auto nodeId : state.out) {
            DFS(app, nodeId, out);
        }
    } else {
        if(state.flagIn) {
            return;
        }
        state.flagIn = true;
        
        for(auto nodeId : state.in) {
            DFS(app, nodeId, out);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<State> application(n);
    
    for(int i = 0; i < n; i++) {
        auto & state = application[i];
        cin >> state.action;
    }
    
    for(int j = 0; j < m; j++) {
        int from, to;
        cin >> from >> to;
        --from; --to;
        auto & stateFrom = application[from];
        stateFrom.out.push_back(to);
        
        auto & stateTo = application[to];
        stateTo.in.push_back(from);
    }
        
    vector<future<void> > promisses;
    for(int k = 0; k < n; k++) {
        auto & state = application[k];   
        
        bool out;
        if(state.action == 1) {
            out = true;
        } else if (state.action == 2) {
            out = false;
        } else {
            continue;
        }
        
        auto f = async(DFS, application, k, out);
        promisses.push_back(f);
    }
    
    for(auto & p : promisses) {
        p.get();
    }

    for(auto & state : application) {
        if(state.flagIn && state.flagOut) {
            cout << 1 << " ";
        } else {
            cout << 0 << " ";
        }
    }
    
    return 0;
}