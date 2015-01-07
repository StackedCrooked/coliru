#include <cstdlib>
#include <iostream>
#include <memory>

class ButterflyWithBigResource {
public:

    //    If I uncomment just this line, I get an error
//        ButterflyWithBigResource(const ButterflyWithBigResource& other) = default;
        
        ButterflyWithBigResource(ButterflyWithBigResource&& other) = default;
        ButterflyWithBigResource& operator=(ButterflyWithBigResource&&) = default;

    //    If I uncomment just this line, I get an error
        ButterflyWithBigResource(const ButterflyWithBigResource& other) = delete;

    //   With both above lines commented out, I get no errors, and the program runs fine.

    ButterflyWithBigResource(std::unique_ptr<int>&& bigResource) :
    bigResource(std::move(bigResource)) {

    }

    const int& getResource() {
        return *bigResource;
    }

private:
    std::unique_ptr<int> bigResource;
};

class CaterpillarWithBigResource {
public:

    CaterpillarWithBigResource(int bigResource) :
    bigResource(new int(bigResource)) {

    }

    ButterflyWithBigResource toButterfly() && {
        return ButterflyWithBigResource(std::move(bigResource));
    }
private:
    std::unique_ptr<int> bigResource;
};

/*
 * 
 */
int main(int argc, char** argv) {
    CaterpillarWithBigResource caterpillarWithBigResource(5);
    ButterflyWithBigResource butterflyWithBigResource(std::move(caterpillarWithBigResource).toButterfly());
    std::cout << butterflyWithBigResource.getResource() << std::endl;
    return 0;
}
