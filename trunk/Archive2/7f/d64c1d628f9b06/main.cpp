#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct subject
{
    std::string category;
    std::string sub_category;
};

struct less
{
    bool operator() ( const subject& a, const subject& b ) const
    {
        // order by sub_category
        if( a.sub_category < b.sub_category ) return true ;
        if( a.sub_category > b.sub_category ) return false ;

        // Rules for deleting are if
        // instance of Subject ->category = " Land " OR if category = "Jungle" 
        // then delete other duplicate object
        // therefore, if sub_caegory is the same, subject with category
        // "Land" or "Jungle" should appear earlier in the sorted sequence
        return ( ( a.category == "Jungle" ) || ( a.category == "Land" ) ) >
               ( ( b.category == "Jungle" ) || ( b.category == "Land" ) ) ;

    }
};

struct equal
{
    // I want my std::vector to have only those objects whose's sub_category are unique.
    bool operator() ( const subject& a, const subject& b ) const
    { return a.sub_category == b.sub_category ; }
};


int main()
{
    std::vector<subject> seq {  { "Animal", "Tiger" },
                                { "Citizenship", "Russia" },
                                { "Online shop", "Amazon" },
                                { "Jungle", "Amazon" },
                                { "Animal", "Lion" },
                                { "Stuffed toy", "Tiger" },
                                { "Language", "English" },
                                { "Language", "American" },
                                { "Language", "French" },
                                { "Animal", "Cow" },
                                { "Citizenship", "American" },
                                { "Land", "Russia" } } ;
    
    // http://en.cppreference.com/w/cpp/algorithm/sort
    std::sort( std::begin(seq), std::end(seq), less() ) ;
    
    // http://en.cppreference.com/w/cpp/algorithm/unique
    seq.erase( std::unique( std::begin(seq), std::end(seq), equal() ), seq.end() ) ;

    for( const subject& s : seq ) std::cout << s.category << " - " << s.sub_category << '\n' ;
}
