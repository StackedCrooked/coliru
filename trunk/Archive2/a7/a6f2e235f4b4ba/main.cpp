template <typename Allocator>
class X : Allocator::template rebind<implementation_detail_t>::other {
    
	// 1)
	typedef Allocator allocator_type;
	
	// 2)
	typedef typename Allocator::template rebind<implementation_detail_t>::other allocator_type;
	
};