#include <iostream>
#include <boost/multi_array.hpp>

struct LVoxel
{
  int type;
  LVoxel() : type(-1) {}
  void setBlockType(int t) { type = t; }
  int getBlockType () { return type; }
  void setActive(bool) {}
};

const int CHUNK_HEIGHT = 128;
const int CHUNK_SIZE = 16;

typedef boost::multi_array<LVoxel, 3> array_type;
typedef array_type::index index;
array_type blockArray(boost::extents[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE]);

void voo()
{
    // Create the blocks
    for (index i = 0; i < CHUNK_SIZE; i++)
    {
        for (index j = 0; j < CHUNK_HEIGHT; j++)
        {
            for (index k = 0; k < CHUNK_SIZE; k++)
            {
                LVoxel block;
                if (j < 3)
                {
                    block.setBlockType(0);
                }
                else if (j >= 3 && j <= 50)
                {
                    block.setBlockType(1);
                }
                else if (j > 50)
                {
                    block.setActive(false);
                    block.setBlockType(-1);
                }
                blockArray[i][j][k] = block;
            }
        }
        std::cout << blockArray[i][0][0].getBlockType();
    }
}
int main()
{
  voo();
}