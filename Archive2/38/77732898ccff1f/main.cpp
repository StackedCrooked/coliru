#include <map>
#include <iostream>
#include <memory>

struct Media {
    virtual ~Media() = default;
};

struct AudioLibrary : Media {
    ~AudioLibrary() {
        std::cout << "~AudioLibrary\n";
    }
};

struct VideoLibrary : Media {
    ~VideoLibrary() {
        std::cout << "~VideoLibrary\n";
    }
};
    

int main() {
    std::map<int, std::unique_ptr<Media>> map;
    map[0] = std::unique_ptr<Media>(new AudioLibrary());
    map[1] = std::unique_ptr<Media>(new VideoLibrary());
}