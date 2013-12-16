#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <vector>
#include <fstream>

struct BasicBlock {
    unsigned int id;
    unsigned int start_address;
    unsigned int end_address;
    std::vector<BasicBlock*>* outgoing;
    std::vector<BasicBlock*>* incoming;
};

// BOOST_CLASS_TRACKING(BasicBlock, boost::serialization::track_always)

namespace boost {
    namespace serialization {
        template<class Archive>
            void save(Archive & archive, const BasicBlock& basic_block, const unsigned int version) {
                archive & basic_block.id;
                archive & basic_block.start_address;
                archive & basic_block.end_address;
                archive & basic_block.incoming;
                archive & basic_block.outgoing;
            }

        template<class Archive>
            void load(Archive & archive, BasicBlock& basic_block, const unsigned int version) {
                archive & basic_block.id;
                archive & basic_block.start_address;
                archive & basic_block.end_address;
                archive & basic_block.incoming;
                archive & basic_block.outgoing;
            }
    }
}

BOOST_SERIALIZATION_SPLIT_FREE(BasicBlock)

int main()
{
    BasicBlock root
    {
        1, 2, 3,
        new std::vector<BasicBlock*> { new BasicBlock { 4, 5, 6, nullptr, nullptr } },
        new std::vector<BasicBlock*> { &root } // cyclic!
    };

    boost::archive::text_oarchive ar(std::cout);
    ar << root;
     
    // everything leaked :)
}
