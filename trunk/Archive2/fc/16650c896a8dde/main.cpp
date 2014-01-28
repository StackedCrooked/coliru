#include <iostream>
#include <functional>
using namespace std;

class VmapPlayer
{
public:
    void startPlayback();
    void playAdBreak(int adBreak, void (VmapPlayer::*callback)());
    void playSingleAd(int ad, std::function<void (VmapPlayer&)>);
};

void VmapPlayer::playSingleAd(int, std::function<void (VmapPlayer&)> callback)
{
    cout << "i am here" << endl;
    callback(*this);
}

void VmapPlayer::playAdBreak(int adBreak, void (VmapPlayer::*callback)())
{
    using namespace std::placeholders;
    auto cb = std::bind(&VmapPlayer::playAdBreak, _1, adBreak, callback);
    playSingleAd(123, cb);
}

void VmapPlayer::startPlayback()
{
    playAdBreak(456, &VmapPlayer::startPlayback);
}

int main()
{
    VmapPlayer p;
    // p.startPlayback(); // <--- INFINITE RECURSION!!
}