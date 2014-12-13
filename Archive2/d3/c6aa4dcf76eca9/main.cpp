#include <boost/serialization/vector.hpp>

class Block
{
   public:
     int blockType;
     std::vector<uint8_t> data;

   private:
       friend class boost::serialization::access;
       template <typename Ar> void serialize(Ar& ar, unsigned) {
               ar & blockType;
               ar & data;
           }
};

class Container
{
   public:
       std::vector<std::vector<Block>> block_lists;

   private:
       friend class boost::serialization::access;
       template <typename Ar> void serialize(Ar& ar, unsigned) {
               ar & block_lists;
           }
};

#include <boost/archive/text_oarchive.hpp>

int main()
{
    Container const letshavesome = {
        { // block_lists
            {
                Block { 1, { 0x11, 0x12, 0x13, 0x14 } },
                Block { 2, { 0x21, 0x22, 0x23, 0x24 } },
                Block { 3, { 0x31, 0x32, 0x33, 0x34 } },
            },
            {
                Block { 4, { 0x41, 0x42, 0x43, 0x44 } },
                Block { 5, { 0x51, 0x52, 0x53, 0x54 } },
                Block { 6, { 0x61, 0x62, 0x63, 0x64 } },
            },
        }
    };

    boost::archive::text_oarchive oa(std::cout);
    oa << letshavesome;
}
