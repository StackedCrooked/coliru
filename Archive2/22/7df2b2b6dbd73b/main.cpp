/* 
 * File:   defecate_spirit.cpp
 * Author: crastinus
 *
 * Created on 5 Февраль 2014 г., 8:01
 */
//#define BOOST_SPIRIT_DEBUG

#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <boost/chrono.hpp>

std::string header_string =
//       "HTTP/1.1 200 Ok \r\n" //Тестовый вариант без заголовка
        "server: nginx \r\n"
        "Date: Mon, 03 Feb 2014 17:48:49 GMT \r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Transfer-Encoding: chunked \r\n"
        "Connection: close\r\n"
        "Cache-Control: no-cache,no-store,max-age=0,must-revalidate \r\n"
        "Expires: Mon, 03 Feb 2014 17:48:50 GMT\r\n"
        "\tLast-Modified: Mon, 03  Feb 2014 17:48:50 GMT \r\n"
 //       "P3P: policyref=\"/w3c/p3p.xml\", CP=\"NON DSP ADM DEV PSD IVDo OUR IND STP PHY PRE NAV UNI\" \r\n"
//        "X-Frame-Options: DENY \r\n"
//        "X-XRDS-Location: http://openid.yandex.ru/server_xrds/\r\n"
        "Content-Encoding: gzip\r\n"
        "Content-Length: 3122\r\n\r\n "
        
        /*Добавлены для полноты. На них парсер не должен срабатывать*/
        "Server: server3\r\n"
        "Some val : some text here after header\r\n\r\n";

/*Поля записаны в такой форме для уменьшения различия между
 названиями заголовков и этими полями*/
enum Fields {
    Server = 0,
    Date,
    Content_Type,
    Transfer_Encoding,
    Connection,
    Cache_Control,
    Last_Modified,
    Expires,
    Content_Encoding,
    Content_Length,
    /*Нестандартизированные поля*/
    P3P,
    X_Frame_Options,
    X_XRDS_Location
};

#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/phoenix/stl/container.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi_skip.hpp>
#include <boost/spirit/include/qi_no_skip.hpp>
#include <boost/spirit/home/phoenix/operator.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/qi_no_case.hpp>

namespace qi = boost::spirit::qi;
typedef boost::variant<int,std::string>               spirit_variant;
typedef std::map<int,spirit_variant>                  spirit_result_type;        /*Для int map быстрее*/
typedef std::unordered_map<std::string,std::string>   getline_result_type;
    

using boost::spirit::ascii::space_type;
using boost::spirit::ascii::space;

    

/*Парсер, который создает словарь из  http-заголовка*/
template<typename Iter, typename Skipper = space_type>
struct header : qi::grammar<Iter, spirit_result_type(), Skipper> 
{
    header() : header::base_type(res)
    {
        /*все отсутсвующие ключи не будут обработаны*/
        key = (qi::no_case[qi::lit("Server")])             [qi::_val = Server]             |
              (qi::no_case[qi::lit("Date") ])              [qi::_val = Date]               |
              (qi::no_case[qi::lit("Content-Type")])       [qi::_val = Content_Type]       |
              (qi::no_case[qi::lit("Transfer-Encoding")])  [qi::_val = Transfer_Encoding]  |
              (qi::no_case[qi::lit("Connection")] )        [qi::_val = Connection]         |
              (qi::no_case[qi::lit("Cache-Control")])      [qi::_val = Cache_Control]      |
              (qi::no_case[qi::lit("Last-Modified")])      [qi::_val = Last_Modified]      |
              (qi::no_case[qi::lit("Expires")]    )        [qi::_val = Expires]            |
              (qi::no_case[qi::lit("Content-Encoding")])   [qi::_val = Content_Encoding]   |
              (qi::no_case[qi::lit("Content-Length")])     [qi::_val = Content_Length] ;
              
        values = qi::no_skip[+(qi::char_ - qi::lit("\r\n") )];
        valuei =  qi::int_ >> qi::no_skip[ qi::lit("\r\n") ];
       
        value = (valuei | values);
        
        res = +(key 
                >> qi::lit(":") 
                >> value  
                >> qi::no_skip[!qi::lit("\r\n\r\n")]  /*В этом месте заканчивается*/
               );
        
        BOOST_SPIRIT_DEBUG_NODES((key)(res)(value));
    }
    
    qi::rule<Iter, spirit_result_type(), Skipper> res;
    qi::rule<Iter, std::string(), Skipper> values;    
    qi::rule<Iter, int(), Skipper> valuei;
    qi::rule<Iter,spirit_variant(),Skipper> value;
    qi::rule<Iter, int(), Skipper> key;
};

#define PRINT_(field) std::cout << #field << ":" << field << std::endl;
/* Это легко генерируется макросом*/
struct spirit_result_type2{
    
    std::string Server;
    std::string Date;
    std::string Content_Type;
    std::string Transfer_Encoding;
    std::string Connection;
    std::string Cache_Control;
    std::string Last_Modified;
    std::string Expires;
    std::string Content_Encoding;
    int         Content_Length;
    
    spirit_result_type2(){
        clear();
    }
    
    void clear(){
        Server = "";
        Date = "";
        Content_Type = "";
        Transfer_Encoding = "";
        Connection = "";
        Cache_Control = "";
        Last_Modified = "";
        Expires = "";
        Content_Encoding = "";
        Content_Length = 0;
    }
    
    void print(){
        PRINT_(Server);
        PRINT_(Date);
        PRINT_(Content_Type);
        PRINT_(Transfer_Encoding);
        PRINT_(Connection);
        PRINT_(Cache_Control);
        PRINT_(Last_Modified);
        PRINT_(Expires);
        PRINT_(Content_Encoding);
        PRINT_(Content_Length)
    }

};

BOOST_FUSION_ADAPT_STRUCT(
        spirit_result_type2,
        (std::string,Server)
        (std::string,Date)
        (std::string,Content_Type)
        (std::string,Transfer_Encoding)
        (std::string,Connection)
        (std::string,Cache_Control)
        (std::string,Last_Modified)
        (std::string,Expires)
        (std::string,Content_Encoding)
        (int, Content_Length)
)

using boost::phoenix::at_c;

/*Парсер, который  записывает  структуру  из      http-заголовка,
 причем именованному ключу соответсвует значение соответсвующего
 поля заголовка*/
template<typename Iter, typename Skipper = space_type>
struct header_to_array : qi::grammar<Iter, spirit_result_type2(), Skipper> 
{
    header_to_array() : header_to_array::base_type(res)
    {
        /*все отсутсвующие ключи не будут обработаны*/
 
              
        value  =  qi::no_skip[+(qi::char_ - "\r\n")];
        valuei =  qi::int_ >>  qi::no_skip[ qi::lit("\r\n") ];
                                              
       /*Это тоже можно сгенерировать с верхним, только
        макрос будет выглядеть очень хитро.*/
        res = +((qi::no_case[qi::lit("Server")]             >> qi::lit(":") >> value [at_c<Server>(qi::_val)             = qi::_1]) |
                (qi::no_case[qi::lit("Date")]               >> qi::lit(":") >> value [at_c<Date>(qi::_val)               = qi::_1]) |
                (qi::no_case[qi::lit("Content-Type")]       >> qi::lit(":") >> value [at_c<Content_Type>(qi::_val)       = qi::_1]) |
                (qi::no_case[qi::lit("Transfer-Encoding")]  >> qi::lit(":") >> value [at_c<Transfer_Encoding>(qi::_val)  = qi::_1]) |
                (qi::no_case[qi::lit("Connection")]         >> qi::lit(":") >> value [at_c<Connection>(qi::_val)         = qi::_1]) |
                (qi::no_case[qi::lit("Cache-Control")]      >> qi::lit(":") >> value [at_c<Cache_Control>(qi::_val)      = qi::_1]) |
                (qi::no_case[qi::lit("Last-Modified")]      >> qi::lit(":") >> value [at_c<Last_Modified>(qi::_val)      = qi::_1]) |
                (qi::no_case[qi::lit("Expires")]            >> qi::lit(":") >> value [at_c<Expires>(qi::_val)            = qi::_1]) |
                (qi::no_case[qi::lit("Content-Encoding")]   >> qi::lit(":") >> value [at_c<Content_Encoding>(qi::_val)   = qi::_1]) |
                (qi::no_case[qi::lit("Content-Length")]     >> qi::lit(":") >> valuei[at_c<Content_Length>(qi::_val)     = qi::_1]) 
                >> qi::no_skip[!qi::lit("\r\n\r\n")]  /*В этом месте заканчивается*/
               );
        
        BOOST_SPIRIT_DEBUG_NODES((res)(value));
    }
    
    qi::rule<Iter, spirit_result_type2(), Skipper> res;
    qi::rule<Iter, std::string(), Skipper> value;
    qi::rule<Iter, int(), Skipper> valuei;
};


#define PRINT
void parse_n(const std::string& str, const size_t N){
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "Parsing  " << N << " iterations of header \n\n" ;
    std::cout << str << std::endl;
#ifdef PRINT
    std::cout << "--------------------------------------------------------------\n\n\n";
#endif
    typedef std::string::const_iterator iter;
    spirit_result_type2 spirit_result2;
    header_to_array<iter> parser_to_struct;
    
    boost::chrono::high_resolution_clock::time_point  start2 = boost::chrono::high_resolution_clock::now(); 
    
    for (size_t ix = 0; ix < N; ix++){
        
        spirit_result2.clear();
        
        iter begin = str.begin();
        iter end = str.end();
        
        bool result = qi::phrase_parse(begin,end,parser_to_struct,space,spirit_result2);
        
        assert(result);
    }
    boost::chrono::milliseconds ms = boost::chrono::duration_cast<boost::chrono::milliseconds> 
            (boost::chrono::high_resolution_clock::now() - start2);  
    std::cout << "parsing into struct time : " << ms.count() << std::endl;
#ifdef PRINT
    std::cout << "spirit parsing result:\n\n";
    spirit_result2.print();
    std::cout << "--------------------------------------------------------------\n\n\n";
#endif    
    /*
     * -------------------------------------------------------------
     */

    
    
   
    
    spirit_result_type spirit_result;
    header<iter> parser_to_map;
    
    boost::chrono::high_resolution_clock::time_point  start1 = boost::chrono::high_resolution_clock::now();    
    
    for (size_t ix = 0; ix < N; ix++){
        spirit_result.clear();
        iter begin = str.begin();
        iter end = str.end();
        bool result = qi::phrase_parse(begin,end,parser_to_map,space,spirit_result);
        
        assert(result);
    }
    ms = boost::chrono::duration_cast<boost::chrono::milliseconds> 
            (boost::chrono::high_resolution_clock::now() - start1);  
    
    std::cout << "parsing into map time : " << ms.count() << std::endl;
    
#ifdef PRINT
    std::cout << "spirit parsing result:\n\n";
    for (std::pair<const int,spirit_variant>& pr : spirit_result )
        std::cout << pr.first << ":" << pr.second << std::endl;
#endif

    
 
    
}

int main(int argc, char** argv) {

    parse_n(header_string,1000);
    
    return 0;
}

