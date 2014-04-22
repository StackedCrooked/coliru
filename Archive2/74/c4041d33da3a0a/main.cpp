//
//  main.cpp
//  mailbox
//
//  Created by Kočička on 19.04.14.
//  Copyright (c) 2014 Kočička. All rights reserved.
//

#ifndef __PROGTEST__ // !! DO NOT remove

#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
using namespace std;

//=================================================================================================
class CTimeStamp
{
    int         m_year, m_month, m_day, m_hour, m_minute, m_sec;
public:
    CTimeStamp                          ( int               year,
                                         int               month,
                                         int               day,
                                         int               hour,
                                         int               minute,
                                         int               sec );
    int                 Compare         ( const CTimeStamp & x ) const;
    friend ostream &    operator <<     ( ostream          & os,
                                         const CTimeStamp & x );
};

//=================================================================================================
class CMailBody
{
public:
    CMailBody                   () : m_Size(0), m_Data(nullptr) {}
    CMailBody                   ( int               size,
                                 const char      * data );
    CMailBody                   ( const CMailBody & );
    CMailBody                   ( CMailBody && );
    ~CMailBody                   ();
    CMailBody     & operator =                  ( const CMailBody & );
    CMailBody     & operator =                  ( CMailBody && );
    // copy cons/op=/destructor implemented in the class
    friend ostream & operator <<                ( ostream         & os,
                                                 const CMailBody & x )
    {
        return os << "mail body: " << x . m_Size << " B";
    }
private:
    int             m_Size;
    char          * m_Data;
    
//    Obj_trace<CMailBody> xxx;
};
//=================================================================================================
class CAttach
{
public:
    CAttach                                 ( int               x )
    : m_X (x), m_RefCnt ( 1 ) { }
    void            AddRef                                  ( void ) const { m_RefCnt ++; }
    void            Release                                 ( void ) const { if ( !--m_RefCnt ) delete this; }
private:
    int             m_X;
    mutable int     m_RefCnt;
    CAttach                                                 ( const CAttach   & x );
    CAttach       & operator =                              ( const CAttach   & x );
    ~CAttach                                                 ( void ) { }
    
    friend ostream & operator <<                            ( ostream         & os,
                                                             const CAttach   & x )
    {
        return os << "attachment: " << x . m_X << " B";
    }
    
//    Obj_trace<CAttach> xxx;
};
//=================================================================================================

#endif /* __PROGTEST__, DO NOT remove */

class CMail
{
public:
                        CMail           ( const CTimeStamp & timeStamp,
                                          const string     & from,
                                          const CMailBody  & body,
                                          const CAttach    * attach );  // ctor
//                        CMail           ( CTimeStamp      && timeStamp,
//                                          string          && from,
//                                          CMailBody       && body,
//                                          CAttach          * attach );  // ctor pro emplace
//
                        CMail           ( const CMail      & );      // copy ctor
//                        CMail           ( CMail           && );      // move ctor
    
    CMail &             operator =      ( const CMail      & rhs ) = default;    // copy = op
    CMail &             operator =      ( CMail           && rhs ) = default;    // move = op
    
    ~CMail           () { if ( m_Attach ) m_Attach -> Release(); };  // dtor
    const string      & From            ( void ) const;
    const CMailBody   & Body            ( void ) const;
    const CTimeStamp  & TimeStamp       ( void ) const;
    const CAttach     * Attachment      ( void ) const;
    
    friend ostream    & operator <<     ( ostream          & os,
                                         const CMail      & x );
    
//    Obj_trace<CMail>    xxx;
    
private:
    CTimeStamp          m_TimeStamp;
    string              m_From;
    CMailBody           m_Body;
    const CAttach     * m_Attach;
};
//=================================================================================================
class CMailBox
{
public:
    
                                CMailBox    ( void );   // def ctor
    
//    bool                        Delivery    ( const CTimeStamp & timeStamp,
//                                              const string & from,
//                                              const CMailBody & body,
//                                              const CAttach * attach );     // delivery for emplace
    
    bool                        Delivery    ( const CMail      & mail );    // delivery s copy
    bool                        Delivery    ( CMail           && mail );    // delivery s move
    
    bool                        NewFolder   ( const string     & folderName );
    
    bool                        MoveMail    ( const string     & fromFolder,
                                             const string     & toFolder );
    
    list< CMail >               ListMail    ( const string     & folderName,
                                             const CTimeStamp & from,
                                             const CTimeStamp & to ) const;
    
    set< string >               ListAddr    ( const CTimeStamp & from,
                                             const CTimeStamp & to ) const;
private:
    map< string, list<CMail> >  m_Mails;        // key = folder
    
//    Obj_trace<CMailBox> xxx;
};

//--8<-------8<-------8<-------8<-------8<-------8<-------8<-------8<-------8<-------8<-------8<---

#ifndef __PROGTEST__ // !! DO NOT remove

//=================================================================================================
//==== CTimeStamp =================================================================================
//=================================================================================================

CTimeStamp::CTimeStamp( int year, int month, int day, int hour, int minute, int sec )
: m_year(year), m_month(month), m_day(day), m_hour(hour), m_minute(minute), m_sec(sec) {
}


int CTimeStamp::Compare( const CTimeStamp &x) const {
    if ( m_year   == x . m_year &&
        m_month  == x . m_month &&
        m_day    == x . m_day &&
        m_hour   == x . m_hour &&
        m_minute == x . m_minute &&
        m_sec    == x . m_sec ) return 0;
    
    if ( m_year < x . m_year )
        return -1;
    else if ( m_year > x . m_year )
        return 1;
    
    if ( m_month < x . m_month )
        return -2;
    else if ( m_month > x . m_month )
        return 2;
    
    if ( m_day < x . m_day )
        return -3;
    else if ( m_day > x . m_day )
        return 3;
    
    if ( m_hour < x . m_hour )
        return -4;
    else if ( m_hour >  x . m_hour )
        return 4;
    
    if ( m_minute < x . m_minute )
        return  -5;
    else if ( m_minute > x . m_minute )
        return 5;
    
    if ( m_sec < x . m_sec )
        return -6;
    else if ( m_sec > x . m_sec )
        return 6;
    
    // unreachable
    return 0;
}

ostream & operator << ( ostream & os, const CTimeStamp & x ) {
    os << x . m_year << "-" << setfill ('0') << setw(2) << x . m_month << "-" << setfill ('0') << setw(2) << x . m_day << " " << setfill ('0') << setw(2) << x . m_hour << ":" << setfill ('0') << setw(2) << x . m_minute << ":" << setfill ('0') << setw(2) << x . m_sec;
    
    return os;
}

//=================================================================================================
//==== CMailBody ==================================================================================
//=================================================================================================

CMailBody::CMailBody( int size, const char * data ) : m_Size(size) {
    m_Data = new char [size];
    memcpy(m_Data, data, size);
}

CMailBody::CMailBody( const CMailBody & x ) : CMailBody( x.m_Size, x.m_Data ) {
}

CMailBody::CMailBody( CMailBody && x ) {
    *this = move(x);
}

CMailBody & CMailBody::operator=( const CMailBody & rhs ) {
    if ( this != & rhs ) {
        delete m_Data;
        m_Data = new char [rhs . m_Size];
        memcpy( m_Data, rhs . m_Data, rhs . m_Size );
        m_Size = rhs . m_Size;
    }
    return *this;
}

CMailBody & CMailBody::operator=(CMailBody && rhs ) {
    if ( this != & rhs ) {
        delete [] m_Data;
        
        m_Size = rhs . m_Size;
        m_Data = rhs . m_Data;
        
        rhs . m_Size = 0;
        rhs . m_Data = nullptr;
    }
    
    return *this;
}

CMailBody::~CMailBody() {
    delete [] m_Data;
}

#endif /* __PROGTEST__, DO NOT remove */

//=================================================================================================
//==== CMail ======================================================================================
//=================================================================================================

CMail::CMail( const CTimeStamp & timeStamp, const string & from, const CMailBody & body, const CAttach * attach ) : m_TimeStamp(timeStamp), m_From(from), m_Body(body), m_Attach(attach)
{
    
    if ( m_Attach )
        m_Attach -> AddRef();
}

CMail::CMail( const CMail & x ) : CMail( x . m_TimeStamp, x . m_From, x . m_Body, x . m_Attach ) {
    if ( m_Attach )
        m_Attach -> AddRef();
}

//CMail::CMail ( CTimeStamp && timeStamp, string && from, CMailBody && body, CAttach * attach ) {
//    m_Attach = nullptr;
//    m_TimeStamp = move(timeStamp);
//    m_From = move(from);
//    m_Body = move(body);
//    m_Attach = move(attach);
//}

//CMail::CMail( CMail && x ) {
//    *this = move(x);
//}

const string & CMail::From() const {
    return m_From;
}

const CMailBody & CMail::Body() const {
    return m_Body;
}

const CTimeStamp & CMail::TimeStamp() const {
    return m_TimeStamp;
}

const CAttach * CMail::Attachment() const {
    if ( m_Attach )
        m_Attach->AddRef();
    
    return m_Attach;
}

ostream & operator << ( ostream & os, const CMail & x ) {
    os << x . m_TimeStamp << " " << x . m_From << " " << x . m_Body;
    if ( x . m_Attach ) os << " + " << *(x . m_Attach);
    
    return os;
}

//=================================================================================================
//==== CMailBox ===================================================================================
//=================================================================================================

CMailBox::CMailBox() {
    m_Mails.emplace( make_pair("inbox", list<CMail>() ) );
}

bool CMailBox::Delivery( const CMail &mail ) {
    m_Mails["inbox"].emplace_back( mail );
    
    return true;
}

bool CMailBox::Delivery( CMail &&mail ) {
    m_Mails["inbox"].emplace_back( mail );
    
    return true;
}


//bool CMailBox::Delivery( const CTimeStamp & timeStamp, const string & from, const CMailBody & body, const CAttach * attach ) {
//    m_Mails["inbox"].emplace_back( CMail(timeStamp, from, body, attach) );
//    
//    return true;
//}

bool CMailBox::NewFolder( const string &folderName ) {
    auto res = m_Mails.emplace( folderName, list<CMail>() );
    
    return res.second;
}

bool CMailBox::MoveMail( const string &fromFolder, const string &toFolder ) {
    map< string,list<CMail> >::iterator from = m_Mails . find( fromFolder );
    map< string,list<CMail> >::iterator to   = m_Mails . find( toFolder );
    
    // at least one of folders does not exist
    if ( from == m_Mails.end() || to == m_Mails.end() )
        return false;
    
    //    move( from->second.begin(), from->second.end(), back_inserter(to->second) );
    m_Mails[toFolder].splice( m_Mails[toFolder].end(), m_Mails[fromFolder], from->second.begin(), from->second.end() );
    return true;
}

list<CMail> CMailBox::ListMail( const string &folderName, const CTimeStamp &from, const CTimeStamp &to ) const {
    list<CMail> res;
    auto folder = m_Mails . find( folderName );
    
    if ( folder == m_Mails.end() )
        return res;
    
    for ( const auto & p : folder -> second )
        if ( p.TimeStamp().Compare(from) >= 0 && p.TimeStamp().Compare(to) <= 0 )
            res . emplace_back( p );
    
    return res;
}

set<string> CMailBox::ListAddr( const CTimeStamp &from, const CTimeStamp &to ) const {
    set<string> res;
    
    for ( const auto & m : m_Mails )
        for ( const auto & p : m . second )
            if ( p.TimeStamp().Compare(from) >= 0 && p.TimeStamp().Compare(to) <= 0 )
                res.emplace( p.From() );
    
    return res;
}

//--8<-------8<-------8<-------8<-------8<-------8<-------8<-------8<-------8<-------8<-------8<---

//=================================================================================================
//==== main =======================================================================================
//=================================================================================================

#ifndef __PROGTEST__ /* DO NOT remove */
void showMail ( const list<CMail> & l )
{
    for ( list<CMail>::const_iterator it = l . begin (); it != l . end (); ++it )
        cout << *it << endl;
}
void showUsers ( const set<string> & s )
{
    for ( set<string>::const_iterator it = s . begin (); it != s . end (); ++it )
        cout << *it << endl;
}


CMail f(CMail a) { return a; }

int main( void )
{
    
    bool        st;
    list<CMail> mailList;
    set<string> users;
    CAttach   * att;
    //
    //    CTimeStamp xt0( 2014, 3, 31, 15, 24, 13 );
    //    CMailBody xcb0( 14, "mail content 1" );
    //
    //    CMail x00(xt0,"user1@fit",xcb0,NULL);
    //
    
    
    CMail x0(CTimeStamp ( 2014, 3, 31, 15, 24, 13 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 1" ), NULL );
    
    
    CMailBox m0;
    st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 24, 13 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 1" ), NULL ) );
    // st = true
    st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ), "user2@fit.cvut.cz", CMailBody ( 22, "some different content" ), NULL ) );
    // st = true
    att = new CAttach ( 200 );
    st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 11, 23, 43 ), "boss1@fit.cvut.cz", CMailBody ( 14, "urgent message" ), att ) );
    // st = true
    st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 18, 52, 27 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 2" ), att ) );
    // st = true
    att -> Release ();
    att = new CAttach ( 97 );
    st = m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), att ) );
    // st = true
    att -> Release ();
    showMail ( m0 . ListMail ( "inbox",
                              CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                              CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B + attachment: 200 B
     2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
     2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B
     2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B
     2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 200 B
     ---8<---8<---8<---8<---8<---8<---
     */
    showMail ( m0 . ListMail ( "inbox",
                              CTimeStamp ( 2014, 3, 31, 15, 26, 23 ),
                              CTimeStamp ( 2014, 3, 31, 16, 12, 48 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B
     2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B
     ---8<---8<---8<---8<---8<---8<---
     */
    showUsers ( m0 . ListAddr ( CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                               CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     boss1@fit.cvut.cz
     user1@fit.cvut.cz
     user2@fit.cvut.cz
     ---8<---8<---8<---8<---8<---8<---
     */
    showUsers ( m0 . ListAddr ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ),
                               CTimeStamp ( 2014, 3, 31, 16, 12, 48 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     boss1@fit.cvut.cz
     user2@fit.cvut.cz
     ---8<---8<---8<---8<---8<---8<---
     */
    
    //    CMail mail( CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), att );
    //    CMail mail2(CTimeStamp ( 0, 0, 0, 0, 0, 0 ), "", CMailBody ( 1, "" ), NULL );
    //
    //    mail2 = move(mail);
    //    mail = f(CMail(CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), att ));
    
    
    CMailBox m1;
    st = m1 . NewFolder ( "work" );
    // st = true
    st = m1 . NewFolder ( "spam" );
    // st = true
    st = m1 . NewFolder ( "spam" );
    // st = false
    st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 24, 13 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 1" ), NULL ) );
    // st = true
    att = new CAttach ( 500 );
    st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ), "user2@fit.cvut.cz", CMailBody ( 22, "some different content" ), att ) );
    // st = true
    att -> Release ();
    st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 11, 23, 43 ), "boss1@fit.cvut.cz", CMailBody ( 14, "urgent message" ), NULL ) );
    // st = true
    att = new CAttach ( 468 );
    st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 18, 52, 27 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 2" ), att ) );
    // st = true
    att -> Release ();
    st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), NULL ) );
    // st = true
    showMail ( m1 . ListMail ( "inbox",
                              CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                              CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B
     2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
     2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B
     2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B
     2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B
     ---8<---8<---8<---8<---8<---8<---
     */
    showMail ( m1 . ListMail ( "work",
                              CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                              CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     ---8<---8<---8<---8<---8<---8<---
     */
    st = m1 . MoveMail ( "inbox", "work" );
    // st = true
    showMail ( m1 . ListMail ( "inbox",
                              CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                              CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     ---8<---8<---8<---8<---8<---8<---
     */
    showMail ( m1 . ListMail ( "work",
                              CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                              CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B
     2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
     2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B
     2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B
     2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B
     ---8<---8<---8<---8<---8<---8<---
     */
    st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 19, 24, 13 ), "user2@fit.cvut.cz", CMailBody ( 14, "mail content 4" ), NULL ) );
    // st = true
    att = new CAttach ( 234 );
    st = m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 13, 26, 23 ), "user3@fit.cvut.cz", CMailBody ( 9, "complains" ), att ) );
    // st = true
    att -> Release ();
    showMail ( m1 . ListMail ( "inbox",
                              CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                              CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B
     2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B
     ---8<---8<---8<---8<---8<---8<---
     */
    showMail ( m1 . ListMail ( "work",
                              CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                              CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B
     2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
     2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B
     2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B
     2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B
     ---8<---8<---8<---8<---8<---8<---
     */
    st = m1 . MoveMail ( "inbox", "work" );
    // st = true
    showMail ( m1 . ListMail ( "inbox",
                              CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                              CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     ---8<---8<---8<---8<---8<---8<---
     */
    showMail ( m1 . ListMail ( "work",
                              CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                              CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) );
    /*
     ---8<---8<---8<---8<---8<---8<---
     2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B
     2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B
     2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B
     2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B
     2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B
     2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B
     2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B
     ---8<---8<---8<---8<---8<---8<---
     */
    return 0;
    
}
#endif /* __PROGTEST__, DO NOT remove */

