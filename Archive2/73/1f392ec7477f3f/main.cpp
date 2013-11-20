#include <cassert>
#include <string>
#include <vector>

struct SkeletalAnimationChannel {
    
    std::string name;
    double duration;
    double currenttime, lasttime;
	
    SkeletalAnimationChannel() {}
    SkeletalAnimationChannel ( SkeletalAnimationChannel&& ) = default;
    SkeletalAnimationChannel& operator=(SkeletalAnimationChannel&&) = default;

};

struct Container {
    
    std::vector<SkeletalAnimationChannel> arf;
    
    Container() {}
    Container( Container&& ) = default;
    Container& operator=( Container&& ) = default;
    
};

int main () {
    Container no_copy_move_elision{};
    Container c = std::move( no_copy_move_elision );
}