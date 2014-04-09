
#include <atomic>
#include <memory>
#include <vector>
#include <iostream>
#include <thread>
#include <sstream>

namespace lock_free
{
    /**
     * This is a lock free fifo, which can be used for multi-producer, multi-consumer
     * type job queue
     */
    
    template < typename Value >
    struct fifo_node_type
    {
        fifo_node_type( const Value &original ) :
            value( original ),
            next( nullptr ) { }
        
        Value value;
        fifo_node_type *next;
    };
    
    template < typename Value, typename Allocator = std::allocator< fifo_node_type< Value > > >
    class fifo
    {
        public:
            
            typedef Value value_type;
            typedef Allocator allocator_type;
            typedef std::vector< value_type, allocator_type > vector_type;
            
            fifo() :
                start_(),
                end_(),
                allocator_() {}
        
            ~fifo()
            {
                clear();
            }
            
            /**
             * pushes an item into the job queue, may throw if allocation fails
             * leaving the queue unchanged
             */
            template < typename T >
            void push( T &&val )
            {
                node_ptr newnode = create_node( std::forward< T >( val ) );
                
                node_ptr tmp = nullptr;
                start_.compare_exchange_strong( tmp, newnode );
                
                node_ptr prev_end = end_.exchange( newnode );
                if ( prev_end )
                {
                    prev_end->next = newnode;
                }
            }
        
            /**
             * retrieves an item from the job queue.
             * if no item was available, func is untouched and pop returns false
             */
            bool pop( value_type &func )
            {
                auto assign = [ & ]( node_ptr ptr, value_type &value)
                {
                    std::swap( value, ptr->value );
                    destroy_node( ptr );
                };
                return pop_generic( func, assign );
            }
        
            /**
             * clears the job queue, storing all pending jobs in the supplied vector.
             * the vector is also returned for convenience
             */
            vector_type& pop_all( vector_type &unfinished )
            {
                value_type tmp;
                while ( pop( tmp ) )
                {
                    unfinished.push_back( tmp );
                }
                return unfinished;
            }
        
            /**
             * clears the job queue.
             */
            void clear()
            {
                auto del = [ & ]( node_ptr ptr, value_type& )
                {
                    destroy_node( ptr );
                };
                value_type tmp;
                while ( pop_generic( tmp, del ) )
                {
                    // empty
                }
            }
            
            /**
             * returns true if there are no pending jobs
             */
            bool empty() const
            {
                return start_ == nullptr;
            }
            
        private:
            
            typedef fifo_node_type< value_type > node_type;
            typedef node_type* node_ptr;
            typedef std::atomic< node_ptr > node;
        
            fifo( const fifo& );
            fifo& operator = ( const fifo& );
            
            template < typename Assign >
            bool pop_generic( value_type &func, Assign assign )
            {
                node_ptr tmp = start_;
                
                while ( tmp )
                {
                    if ( start_.compare_exchange_weak( tmp, tmp->next ) )
                    {
                        assign( tmp, func );
                        
                        return true;
                    }
                    // if we got here, tmp was set to the value of start_, so we try again
                }
                
                return false;
            }
            
            template < typename T >
            node_ptr create_node( T &&t )
            {
                node_ptr result = reinterpret_cast< node_ptr >( allocator_.allocate( 1 ) );
                new ( result ) node_type( std::forward< T >( t ) );
                return result;
            }
            
            void destroy_node( node_ptr &t )
            {
                allocator_.destroy( t );
                allocator_.deallocate( t, 1 );
            }
            
            node start_, end_;
            allocator_type allocator_;
    };
}

using namespace std;

typedef function< void() > function_type;

typedef lock_free::fifo< function_type > jobqueue;

template < typename T >
T to( const string &str )
{
    T result;
	stringstream( str ) >> result;
	return result;
}

int main( int argc, char *argv[] )
{
	jobqueue queue;
	
	const auto expected = 1e3;
	
	atomic_size_t actual( 0 );
	for ( auto i = 0; i < expected; ++i )
	{
		queue.push(
			[&]()
			{
				++actual;
			}
		);
	}
	
    auto go = [ &queue ]()
	{
		function_type func;
		while ( queue.pop( func ) )
		{
			func();
		}
	};

	auto thread_count = argc > 1 ? to< size_t >( argv[ 1 ] ) : 20;

	vector< thread > threads;
	while ( thread_count-- )
	{
		threads.push_back( thread( go ) );
	}

	for ( auto &t : threads )
	{
		t.join();
	}

	cout << "expected: " << expected << " got: " << actual << endl;

	return ( expected != actual );
}
