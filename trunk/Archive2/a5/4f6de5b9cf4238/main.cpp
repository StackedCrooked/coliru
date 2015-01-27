#include <iostream>
#include <deque>
#include <chrono>
#include <algorithm>
#include <unistd.h>
#include <queue>
#include <vector>
#include <assert.h>

using namespace std;

class DlgManager2{
public:
    DlgManager2(int min, int max, int expirationTime) : _min(min), _max(max), _expirationTime(expirationTime), _isAvailable(_max - _min, true) {}

    int getExpirationTime() const { return _expirationTime; }

    void setExpirationTime(int expirationTime){ _expirationTime = expirationTime; }

    int getNextNumber(){
        cout << "getting next number" << endl;
        auto it = find(_isAvailable.begin(), _isAvailable.end(), true);
        auto result = it == _isAvailable.end() ? -1 : distance(_isAvailable.begin(), it) + _min;

        if (result > 0){
            *it = false;
            _fifo.push(make_pair(time(nullptr), result));
        }
        return result;
    }

    void ReleaseNumber(int number)
    {
        assert(number >= _min && number <= _max);
        _isAvailable[number - _min] = false;
    }

    int ReleaseNextExpiredNumber(){
        auto result = -1;

        while (!_fifo.empty() && _fifo.front().first <= time(nullptr) + _expirationTime){
            if (_isAvailable[_fifo.front().second - _min]){
                _fifo.pop();
            }else{
                result = _fifo.front().second;
                _fifo.pop();
                break;
            }
        }
        return result;
    }
private:
    const int _min;
    const int _max;
    int _expirationTime;
    std::vector<bool> _isAvailable;
    std::queue<std::pair<time_t, int>> _fifo;
};

int main()
{
    cout << "Hello World!" << endl;
    int expTime = 3;
    int min = 1;
    int max = 4;
    
    DlgManager2* obj = new DlgManager2(min, max, expTime);
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;    
    cout << "releasing 2 " << endl;
    obj->ReleaseNumber(2);
    cout << "releasing 3 " << endl;
    obj->ReleaseNumber(3);
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "--------------" << endl;
    sleep(2);
    cout << "expired: " << obj->ReleaseNextExpiredNumber() << endl;
    sleep(2);
    cout << "expired: " << obj->ReleaseNextExpiredNumber() << endl;
    sleep(2);
    cout << "expired: " << obj->ReleaseNextExpiredNumber() << endl;
    sleep(2);
    cout << "expired: " << obj->ReleaseNextExpiredNumber() << endl;
    sleep(2);
    cout << "expired: " << obj->ReleaseNextExpiredNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    cout << "got: " << obj->getNextNumber() << endl;
    
    return 0;
}

