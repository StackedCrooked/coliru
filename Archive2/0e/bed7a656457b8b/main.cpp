#include <cassert>
#include <string>
#include <vector>

struct SkeletalAnimationChannel {
    
    std::string name;
    double duration;
    double currenttime, lasttime;
	
    SkeletalAnimationChannel() {}
    SkeletalAnimationChannel ( SkeletalAnimationChannel&& ) noexcept = default;
    SkeletalAnimationChannel& operator=(SkeletalAnimationChannel&&) noexcept = default;

};

struct Container {
    
    std::vector<SkeletalAnimationChannel> arf;
    
    Container() {}
    Container( Container&& ) noexcept = default;
    Container& operator=( Container&& ) noexcept = default;
    
};

int main () {
    Container no_copy_move_elision{};
    Container c = std::move( no_copy_move_elision );
}