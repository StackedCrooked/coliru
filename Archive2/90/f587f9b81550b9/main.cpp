#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

struct record
{
    std::string user_name ;
    std::size_t password_hash ;
    int amount ;
};

record make_record( std::string name, std::string password, int amount )
{ return { name, std::hash<std::string>()(password), amount } ; }

int main()
{
    const char* const file_name =  "records.txt" ;

    {
        std::vector<record> data ;

        // add some records
        data.push_back( make_record( "alee 4408", "jjjgUGUGU", 2234 ) ) ;
        data.push_back( make_record( "Peter 87", "YUGFUGU", 2000 ) ) ;
        data.push_back( make_record( "JL Borges", "kbbhki", 920 ) ) ;
        data.push_back( make_record( "Daffy Duck", "yf76rt87r87", 1500 ) ) ;

        // write the records into a file
        std::ofstream file(file_name) ;
        for( const record& rec : data )
        {
            file << rec.user_name << "# " // user name terminated by #
                 << rec.password_hash << ' '
                 << rec.amount << '\n' ; // one line per record
        }
    }

    // display the contents of the file (for testing)
    std::cout << "the file contains:\n\n" << std::ifstream(file_name).rdbuf() ;

    std::vector<record> recs_from_file ;
    // read the records from the file
    {

        std::ifstream file(file_name) ;
        record rec ;
        while( std::getline( file, rec.user_name, '#' ) && // read use name, throw away the'#'
                file >> rec.password_hash >> rec.amount >> std::ws ) // throw away the last new line
        {
            recs_from_file.push_back(rec) ;
        }
    }
    std::cout << '\n' << recs_from_file.size() << " records were read\n\n" ;

    // sort the records on amount
    std::sort( recs_from_file.begin(), recs_from_file.end(),
                [] ( const record& a, const record& b ) { return a.amount < b.amount ; } ) ;

    // display the sorted records
    for( std::size_t i = 0 ; i < recs_from_file.size() ; ++i )
    {
        std::cout << i+1 << ". " << recs_from_file[i].user_name << ' '
                   << recs_from_file[i].password_hash << ' '
                   << recs_from_file[i].amount << '\n' ;
    }
}
