#include <memory>
#include <iostream>
 
template <class Ptr>
struct BlockList
{
   // Predefine a memory block 
   struct block;
 
   // Define a pointer to a memory block from the kind of pointer Ptr s
   // If Ptr is any kind of T*, block_ptr_t is block*
   // If Ptr is smart_ptr<T>, block_ptr_t is smart_ptr<block>
   typedef typename std::pointer_traits<Ptr>::template rebind<block> block_ptr_t;
 
   struct block
   {
      std::size_t size;
      block_ptr_t next_block;
   }; 
 
   block_ptr_t free_blocks;
}; 
 
int main()
{
    BlockList<int*> bl1;
    // The type of bl1.free_blocks is block*
 
    BlockList<std::shared_ptr<char>> bl2;
    // The type of bl2.free_blocks is std::shared_ptr<block>
    std::cout << bl2.free_blocks.use_count() << '\n';
}