
// 2014 donated to Public Domain

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

// linked list using sentry (sentinel)
// should compile equally well in C and C++

// here is where you change what this is a list of
typedef int Data;

// this will be our Node, the items in the linked list
// node pointers will be used as 'iterators'
typedef struct NodeTag
{
    struct NodeTag* next;
	struct NodeTag* prev;
	Data data;
} Node;

// this is the 'container'
typedef struct
{
	Node* sentry; // this will be our sentry node
	size_t size;
} List;

// regarding the sentry node:
// sentry->next will point to the first item
// sentry->prev will point to the last item
// if list is empty, sentry will point to itself
// sentry also functions as the 'one past last' marker (end)
// sentry is a 'dummy' item, that makes sure the list is never empty of nodes
// this way, no special cases is needed

// full set of forwards: O(1) unless otherwise noted
void    ListInit      ( List* );                  // this creates a new empty list
Node*   ListBegin     ( List* );                  // pointer to first item of list, or end if empty
Node*   ListEnd       ( List* );                  // pointer to end (one past last)
Node*   ListInsert    ( List*, Node*, Data );     // this inserts new data before node
void    ListPushBack  ( List*, Data );            // adds new item last
void    ListPushFront ( List*, Data );            // adds new item first
Node*   ListErase     ( List*, Node* );           // erase one item. don't call for end
Data    ListPopBack   ( List* );                  // remove last item. don't call on empty list
Data    ListPopFront  ( List* );                  // remove first item. don't call on empty list
void    ListClear     ( List* );                  // erase all items. O(n)
void    ListDelete    ( List* );                  // this destroys the list itself. O(n)
size_t  ListSize      ( List* );                  // returns size of list
bool    ListEmpty     ( List* );                  // returns true if list empty
Data    ListBack      ( List* );                  // returns last item
Data    ListFront     ( List* );                  // returns first item
Node*   ListByIndex   ( List*, size_t );          // return item by index. O(n)

// --- implementation ---

// debug aid

#ifndef NDEBUG
 int allocations = 0;
 void* alloacte( size_t sz ) { ++allocations; return malloc(sz); }
 void deallocate( void* p ) { --allocations; free(p); }
#else
 #define alloacte malloc
 #define deallocate free
#endif

// a note on assert
// assert test its condition, prints an error message and exits program if it's false
// assert do nothing if NDEBUG is defined

// this creates a new empty list
void ListInit( List* lst )
{
	assert( lst );
	Node* sent = (Node*) alloacte( sizeof(*sent) );// make a new sentry node
	assert( sent );
	sent->next = sent;
	sent->prev = sent; // that points to itself
	lst->sentry = sent;
	lst->size = 0;
}

// pointer to first item of list, or end if empty
Node* ListBegin( List* lst )
{
	assert( lst && lst->sentry );
	return lst->sentry->next; // no special-cases for empty list needed when using sentry
}

// pointer to end (one past last)
Node* ListEnd( List* lst )
{
	assert( lst && lst->sentry );
	return lst->sentry;
}

// now we have what we need for iterating through the list
// this is how you do it:
//
// Node* iter = ListBegin( lst );
// while( iter != ListEnd( lst ) ) {
//     DoSomething( iter->data );
//     iter = iter->next;
// }

// helper function to link 2 nodes
static void Link( Node* n1, Node* n2 )
{
	n1->next = n2;
	n2->prev = n1;
}

// this inserts new data before 'here'
Node* ListInsert( List* lst, Node* here, Data data )
{
	assert( lst && lst->sentry && here );
	// create new item
	Node* item = (Node*) alloacte( sizeof(*item) );
	assert( item );
	// copy in data
	item->data = data;
	// link in new node
	// item comes before here, so inbetween here->prev and here
	Link( here->prev, item );
	Link( item, here );
	// no special cases needed when using sentry
	// update size
	++lst->size;
	return item;
}

// adds new item last
void ListPushBack( List* lst, Data d )
{
	ListInsert( lst, ListEnd( lst ), d );
}

// adds new item first
void ListPushFront( List* lst, Data d )
{
	ListInsert( lst, ListBegin( lst ), d );
}

// now we can add items to the list, lets remove them

// erase one item. don't call for end
Node* ListErase( List* lst, Node* here )
{
	assert( lst && lst->sentry && here && here != lst->sentry );
	// save next item for return value
	Node* nxt = here->next;
	// unlink item. no special cases needed for empty list when using sentry
	Link( here->prev, here->next );
	// delete item
	deallocate( here );
	// update size
	--lst->size;
	return nxt;
}

// this is how you iterate a list, while deleting some items that fulfils some criteria:
//
// Node* iter = ListBegin( lst );
// while( iter != ListEnd( lst ) ) {
//     DoSomething( iter->data );
//     if( SomeCriteria( iter->data ) )
//         iter = ListErase( lst, iter ); // this is why ListErase returns a Node*
//     else
//         iter = iter->next;
// }

// remove last item. don't call on empty list
Data ListPopBack( List* lst )
{
	assert( !ListEmpty( lst ) );
	Node* iter = lst->sentry->prev;
	Data ret = iter->data;
	ListErase( lst, iter );
	return ret;
}

// remove first item. don't call on empty list
Data ListPopFront( List* lst )
{
	assert( !ListEmpty( lst ) );
	Node* iter = lst->sentry->next;
	Data ret = iter->data;
	ListErase( lst, iter );
	return ret;
}

// and a way to clear the list

// erase all items
void ListClear( List* lst )
{
	assert( lst && lst->sentry );
	Node* p = lst->sentry->next;
	Node* n;
	while( p != lst->sentry )
	{
		n = p->next;
		deallocate( p );
		p = n;
	}
	lst->size = 0;
}

// this destroys the list itself
void ListDelete( List* lst )
{
	ListClear( lst );
	deallocate( lst->sentry );
	lst->sentry = 0;
}

// a few convenience functions

// returns size of list
size_t ListSize( List* lst )
{
	assert( lst && lst->sentry );
	return lst->size;
}

// returns true if list empty
bool ListEmpty( List* lst )
{
	assert( lst && lst->sentry );
	return lst->sentry->next == lst->sentry;
}

// accessors

// returns last item
Data ListBack( List* lst )
{
	assert( ! ListEmpty( lst ) );
	return lst->sentry->prev->data;
}

// returns first item
Data ListFront( List* lst )
{
	assert( ! ListEmpty( lst ) );
	return lst->sentry->next->data;
}

// return iterator by index
Node* ListByIndex( List* lst, size_t idx )
{
	assert( lst && lst->sentry );
	assert( idx < lst->size );
	Node* iter = ListBegin( lst );
	while( idx-- ) iter = iter->next; // this loop is why index access in O(n)
	return iter;
}


// and now we have most we need for a linked list :D

bool ListIntegrityCheck( List* lst )
{
	if( ! lst ) return false;
	if( ! lst->sentry ) return false;
	Node* prev = lst->sentry;
	Node* curr = lst->sentry->next;
	size_t sz = 0;
	while( curr != lst->sentry )
	{
		if( sz >= lst->size ) return false;
		++sz;
		if( curr->prev != prev ) return false;
		prev = curr;
		curr = curr->next;
	}
	if( sz != lst->size ) return false;
	if( lst->sentry->prev != prev ) return false;

	return true;
}


char* TestList()
{
	List list;

	ListInit( &list );
	
	assert( ListIntegrityCheck( &list ) );

	ListPushBack( &list, 1 );
	ListPushBack( &list, 2 );
	ListPushBack( &list, 3 );
	ListPushBack( &list, 4 );

	// list should be 1, 2, 3, 4
	
	assert( ListIntegrityCheck( &list ) );
	
	Node* iter = ListBegin( &list );
	while( iter != ListEnd( &list ) )
	{
		iter->data *= 3; // triple values to 3, 6, 9, 12
		if( iter->data % 2 )
			iter = ListErase( &list, iter ); // remove odd, now 6, 12
		else
			iter = iter->next;
	}
	
	assert( ListIntegrityCheck( &list ) );

	static char buffer[256];
	static char str[256];

	buffer[0] = str[0] = 0;

	iter = ListBegin( &list );
	while( iter != ListEnd( &list ) )
	{
		sprintf( str, "%d ", iter->data ); // print
		strcat( buffer, str ); // and concatenate
		iter = iter->next;
	}

	ListDelete( &list );

    assert( allocations == 0 );

	return buffer; // this should return "6 12 "
}

int main() { printf("%s\n",TestList()); }
