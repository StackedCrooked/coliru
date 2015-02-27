
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef
struct Item
{
    struct Item* next;
    char* string;
} Item;

typedef int (*CompFunc)( const char* s1, const char* s2 );

void SortList( Item* sentry, CompFunc cmp )
{
    Item* lst = sentry->next;
	Item* end = sentry;
	Item* tail;

	if(lst == end) return;
	if(lst->next == end) return;

	int blk_sz=1;

	while (true)
	{
		Item* a = lst;
		lst = tail = end;
		int num_merge = 0; 
		while (a!=end)
		{
			++num_merge;
			Item* b = a->next;
			int asz = 1;
			while ( (asz < blk_sz) && (b!=end) )
			{
				++asz;
				b = b->next;
			}
			int bsz = blk_sz;
			while ( asz || (bsz && (b!=end)) )
			{
				Item* src;
				#define SRC(x) x; x = x->next; -- x##sz
				if ( !asz ) {
					src = SRC(b); 
				} else if ( (b==end) || !bsz ) {
					src = SRC(a);
				} else if ( cmp(a->string,b->string)<0 ) {
					src = SRC(a);
				} else {
					src = SRC(b);
				}
				#undef SRC
				if (tail!=end)
					tail->next = src;
				else
					lst = src;
				tail = src;
			}
			a = b;
		}
		tail->next = end;
		if (num_merge <= 1) break;
		blk_sz <<= 1;
	}

	sentry->next = lst;
}

void Add( Item* sentry , char* str )
{
    Item* itm = malloc(sizeof(Item));
    itm->string = str;
    itm->next = sentry->next;
    sentry->next = itm;
}

void PrintList( Item* sentry )
{
    Item* p = sentry->next;
    while( p != sentry )
    {
        printf( "%s ",p->string );
        p = p->next;
    }
    printf("\n");
}

void ClearList( Item* sentry )
{
    Item* p = sentry->next;
    while( p != sentry )
    {
        Item* nxt = p->next;
        free(p);
        p = nxt;
    }
}


int main()
{
    Item sentry;
    sentry.next = &sentry;
    
    Add( &sentry, "aaa" );
    Add( &sentry, "ccc" );
    Add( &sentry, "bbb" );
    
    PrintList( &sentry );
    
    SortList( &sentry, &strcmp );
    
    PrintList( &sentry );
    
    ClearList( &sentry );

}

