ClassA & operator << ( ClassA &, int32_t )
{
    ...
}


class ClassMain
{
public:
    insert( ClassA & c ) const;
    ...
private:
    std::set<int> m_setContainer;
};

struct  InsertOpt : binary_function<ClassA, int, ClassA&>
{
        ClassA & operator( )( ClassA & c, int val ) const
        {
                c << val;
                return c;
        }
};

void ClassMain::insert( ClassA & c ) const
{
    // Case I: the for loop works
    for ( std::set<int>::const_iterator iter = m_setContainer.begin( );
          iter != m_setContainer.end( ); ++iter )
    {
            c << *iter; // operator<<( c, *iter );
    }

    // Case II: doesn't work
    for_each( m_setContainer.begin( ), m_setContainer.end( ), bind1st( InsertOpt(), c ) );


}