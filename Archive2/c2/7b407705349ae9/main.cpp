#include <iostream>
#include <deque>

using namespace std;

int main() {
    class drift_t{ //It works
      public:
        int _drift;
        int _immediateDrift;
        drift_t() : _drift(0), _immediateDrift(0) {}
        drift_t(int d, int expected) : _drift(d), _immediateDrift(expected) {}
        drift_t(const drift_t& ro) : _drift(ro._drift), _immediateDrift(ro._immediateDrift) {}
        drift_t& operator = (const drift_t& ro) { this->_drift = ro._drift; this->_immediateDrift = ro._immediateDrift; return *this; }
      } ;
}