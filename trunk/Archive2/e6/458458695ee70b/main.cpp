#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>


using namespace std;
#endif /* __PROGTEST__ */

//=========================
//======= myString ========
//=========================
class myString {
    char * data;
	size_t size;
	
	friend std::ostream & operator << ( std::ostream &os, const myString &);
	void		print		( std::ostream & os ) const;
	
public:
    myString	();
    myString	( const char * );
    myString	( const myString & s );
    ~myString	();
	myString &	operator+=	( const myString & rhs );
	myString &	operator =	( const myString & rhs );
    bool        operator == ( const myString & rhs ) const;
    char *      c_str() const;
    
};

//---8<--- IMPLEMENTATION ---8<---

std::ostream & operator << ( std::ostream & os, const myString & s ) {
	s.print( os );
	return os;
}

myString operator + ( const myString & lhs, const myString & rhs ) {
	myString res(lhs);
	res += rhs;
	return res;
}

myString::myString() : data(NULL), size(0) {
	
}

myString::myString(const myString & s) : size(s.size) {
	data = new char [size+1];
	strncpy(data, s.data, size+1);
}

myString::myString( const char * s ) {
	size = strlen(s);
	data = new char [size+1];
	strncpy(data, s, size+1);
}

myString & myString::operator+=(const myString &rhs) {
	data = (char*)realloc(data, size+rhs.size+1);
	strncpy(data+size, rhs.data, rhs.size+1);
	size += rhs.size;
	return *this;
}

myString & myString::operator=(const myString & rhs) {
	if ( &rhs != this ) {
		data = (char*)realloc(data, rhs.size+1);
		strncpy(data, rhs.data, rhs.size+1);
		size = rhs.size;
	}
	return *this;
}

bool myString::operator == ( const myString & rhs ) const {
    int res = strcmp(this -> c_str(), rhs.c_str());
    return res == 0;
}

char * myString::c_str() const {
    return data;
}



void myString::print( std::ostream & os ) const {
	os << data;
}

myString::~myString() {
    //    std::cout << "destruktim string" << std::endl;
	delete [] data;
}

//=========================
//======= myVector ========
//=========================

template <typename T>
class myVector {
public:
    static const size_t INIT_CAPACITY = 5;
    static const int    GROW_FACTOR   = 2;
    //    typedef char * val_type;    // co ukladam do vektoru
    
    T* m_data;
    
    size_t m_size;
    size_t m_capacity;
public:
                myVector    ();
                myVector    ( const myVector & );
               ~myVector    ();
    size_t      size        () const;
    size_t      capacity    () const;
    myVector &  operator =  ( const myVector & );
    void        push_back   ( const T & );
    T &         operator[]  ( int );
    T const &   operator[]  ( int ) const;
    myVector *  copy        () const;
    void        clear       ();
    
};

//---8<--- IMPLEMENTATION ---8<---

template <typename T>
myVector<T>::myVector() : m_size (0), m_capacity(INIT_CAPACITY) {
    m_data = new T [INIT_CAPACITY];
}

template <typename T>
myVector<T>::myVector (const myVector & x ) : m_size(x.m_size), m_capacity(x.m_capacity) {
    m_data = new T [x.m_capacity];
    
    for ( int i = 0; i < static_cast<int>(m_size); ++ i ) {
        m_data[i] = x.m_data[i];
    }
}

template <typename T>
myVector<T>::~myVector() {
    delete [] m_data;
}

template <typename T>
size_t myVector<T>::size() const {
    return  m_size;
}

template <typename T>
size_t myVector<T>::capacity() const {
    return m_capacity;
}

template <typename T>
myVector<T> & myVector<T>::operator=(const myVector & rhs) {
    if ( this != & rhs ) {
        m_size = rhs . m_size;
        m_capacity = rhs . m_capacity;
        for ( int i = 0; i < static_cast<int>(m_size); i ++) {
            m_data[i] = rhs . m_data[i];
        }
    }
    return *this;
}

template <typename T>
void myVector<T>::push_back( const T & x ) {
    if ( m_size == m_capacity ) {
        T * new_data = new T[m_capacity * GROW_FACTOR];
        for ( int i = 0 ; i < static_cast<int>(m_size); ++ i ) {
            new_data[i] = m_data[i];
        }
        m_capacity *= GROW_FACTOR;
        delete [] m_data;
        m_data = new_data;
    }
    
    T new_item(x);
    m_data[m_size++] = new_item;
}

template <typename T>
T & myVector<T>::operator [] ( int idx ) {
    return m_data[idx];
}

template <typename T>
T const & myVector<T>::operator[]( int idx) const {
    return m_data[idx];
}

template <typename T>
myVector<T> * myVector<T>::copy() const {
    return new myVector(*this);
}

template <typename T>
void myVector<T>::clear() {
    delete [] m_data;
    m_data = new T [INIT_CAPACITY];
    m_size = 0;
    m_capacity = INIT_CAPACITY;
}

//=========================
//======= CAccount ========
//=========================

class CAccount {
    friend class CBank;

    struct s_transaction {
        myString otherAccnt;
        int amount;
        myString signature;


        s_transaction() : otherAccnt(""), amount(0), signature("") {}
        s_transaction( const char * other, int x, const char * s) : otherAccnt(myString(other)), amount(x), signature(myString(s)) {};

    };

 myString m_id;
 int m_initBallance;
    myVector<s_transaction> m_transactions;

 friend std::ostream & operator << ( std::ostream &os, const CAccount &);
 void print ( std::ostream & os ) const;
public:
    CAccount () : m_id(""), m_initBallance(0) {};
    CAccount ( myString & id, int initBalance );
                CAccount ( myString id, int initBalance );
public:
 void transaction ( const char *, int, const char * );
    int Balance ();
};

//---8<--- IMPLEMENTATION ---8<---

void CAccount::print ( std::ostream & os ) const {
    int sum = m_initBallance;

    os << m_id << ":" << endl
    << "   " << m_initBallance << endl;
    for ( int i = 0; i < static_cast<int>(m_transactions.size()); ++ i ) {
        os << " ";
        m_transactions[i].amount < 0 ? os << "- " : os << "+ ";
        os << abs(m_transactions[i].amount) << ",";
        m_transactions[i].amount < 0 ? os << " to: " : os << " from: ";
        os << m_transactions[i].otherAccnt << ", sign: " << m_transactions[i].signature << endl;
        sum += m_transactions[i].amount;
    }
    os << " = " << sum << endl;
}

std::ostream & operator << ( std::ostream & os, const CAccount & a ) {
    a.print(os);
    return os;
}

CAccount::CAccount(myString & id, int initBalance ) : m_id(id), m_initBallance(initBalance) {
}

CAccount::CAccount(myString id, int initBalance ) : m_id(id), m_initBallance(initBalance) {
}

void CAccount::transaction( const char * otherAccnt, int x, const char * signature ) {
    s_transaction t( otherAccnt, x, signature);
    m_transactions.push_back(t);
}

int CAccount::Balance() {
    int sum = m_initBallance;

    for ( int i = 0; i < static_cast<int>(m_transactions.size()); ++ i ) {
        sum += m_transactions[i].amount;
    }

    return sum;
}


//=========================
//======== CBank ==========
//=========================


class CBank
{
public:
 bool NewAccount ( const char * accID,
        int initialBalance );
 bool Transaction ( const char * debAccID,
        const char * credAccID,
        int amount,
        const char * signature );
    bool TrimAccount ( const char * accID );

    CAccount & Account ( const char * );


private:
    myVector<CAccount> m_accounts;

    bool AccountExists ( const char * accID, int & idx ) const;
};

//---8<--- IMPLEMENTATION ---8<---

bool CBank::NewAccount(const char *accID, int initialBalance) {
    int dummy;
    if ( AccountExists(accID, dummy) ) return false;

    m_accounts.push_back( CAccount( accID, initialBalance ) );
    return true;
}

bool CBank::Transaction(const char *debAccID, const char *credAccID, int amount, const char *signature) {

    if ( strcmp(debAccID, credAccID) == 0 ) {
        return false;
    }

    int debIdx = 0, credIdx = 0;

    if ( !( AccountExists(debAccID, debIdx) && AccountExists(credAccID, credIdx) ) )
        return false;





    m_accounts[debIdx].transaction(credAccID, amount * -1, signature);
    m_accounts[credIdx].transaction(debAccID, amount, signature);

    return true;
}


bool CBank::TrimAccount(const char *accID) {
    int idx;

    if ( AccountExists(accID, idx) ) {
        m_accounts[idx].m_initBallance = m_accounts[idx].Balance();
        m_accounts[idx].m_transactions.clear();
        return true;
    } else
        return false;
}

CAccount & CBank::Account( const char * acctID) {
    int idx;

    if ( AccountExists(acctID, idx) ) {
        return m_accounts[idx];
    } else
//        cerr << "dodelej vyjimku!";
        throw "nonexistent acctID";



    return m_accounts[0];
}



bool CBank::AccountExists(const char *accID, int & idx ) const {
    for ( int i = 0; i < static_cast<int>(m_accounts.size()); ++ i )
        if ( strcmp( m_accounts[i].m_id.c_str(), accID ) == 0 ) {
            idx = i;
            return true;
        }
    idx = -1;
    return false;
}

void tryAccountPrint( CBank & bank, int no, bool expected, const char * accID ) {
    bool ok = true;

    try {
        clog << bank . Account( accID );
    } catch (...) {
        ok = false;
    }

    if ( ok == expected ) return;

    cerr << "TEST " << no << ": try << bank . Account (\"accID\")" << endl;
    cerr << "expected " << boolalpha << expected << endl;
    cerr << "but got: " << !expected << endl << endl;
}

#ifndef __PROGTEST__

//=========================
//========= main ==========
//=========================

int main(int argc, const char * argv[])
{
    bool status;
    int  balance;
    char accCpy[100], debCpy[100], credCpy[100], signCpy[100];
    CBank a;
    status = a . NewAccount ( "123456", 1000 );
     // status = true
    status = a . NewAccount ( "987654", -500 );
     // status = true
    status = a . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
     // status = true
    status = a . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
     // status = true
    status = a . NewAccount ( "111111", 5000 );
     // status = true
    status = a . Transaction ( "111111", "987654", 290, "Okh6e+8rAiuT5=" );
     // status = true
    balance = a . Account ( "123456" ). Balance ( );
     // balance = -2190
    balance = a . Account ( "987654" ). Balance ( );
     // balance = 2980
    balance = a . Account ( "111111" ). Balance ( );
     // balance = 4710
    cout << a . Account ( "123456" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    123456:
       1000
     - 300, to: 987654, sign: XAbG5uKz6E=
     - 2890, to: 987654, sign: AbG5uKz6E=
     = -2190
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    cout << a . Account ( "987654" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    987654:
       -500
     + 300, from: 123456, sign: XAbG5uKz6E=
     + 2890, from: 123456, sign: AbG5uKz6E=
     + 290, from: 111111, sign: Okh6e+8rAiuT5=
     = 2980
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    cout << a . Account ( "111111" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    111111:
       5000
     - 290, to: 987654, sign: Okh6e+8rAiuT5=
     = 4710
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    status = a . TrimAccount ( "987654" );
     // status = true
    status = a . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
     // status = true
    cout << a . Account ( "987654" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    987654:
       2980
     + 123, from: 111111, sign: asdf78wrnASDT3W
     = 3103
    ---8<---8<---8<---8<---8<---8<---8<---
    */

    CBank c;
    strncpy ( accCpy, "123456", sizeof ( accCpy ) );
    status = c . NewAccount ( accCpy, 1000 );
     // status = true
    strncpy ( accCpy, "987654", sizeof ( accCpy ) );
    status = c . NewAccount ( accCpy, -500 );
     // status = true
    strncpy ( debCpy, "123456", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "XAbG5uKz6E=", sizeof ( signCpy ) );
    status = c . Transaction ( debCpy, credCpy, 300, signCpy );
     // status = true
    strncpy ( debCpy, "123456", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "AbG5uKz6E=", sizeof ( signCpy ) );
    status = c . Transaction ( debCpy, credCpy, 2890, signCpy );
     // status = true
    strncpy ( accCpy, "111111", sizeof ( accCpy ) );
    status = c . NewAccount ( accCpy, 5000 );
     // status = true
    strncpy ( debCpy, "111111", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "Okh6e+8rAiuT5=", sizeof ( signCpy ) );
    status = c . Transaction ( debCpy, credCpy, 2890, signCpy );
     // status = true
    balance = c . Account ( "123456" ). Balance ( );
     // balance = -2190
    balance = c . Account ( "987654" ). Balance ( );
     // balance = 5580
    balance = c . Account ( "111111" ). Balance ( );
     // balance = 2110
    cout << c . Account ( "123456" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    123456:
       1000
     - 300, to: 987654, sign: XAbG5uKz6E=
     - 2890, to: 987654, sign: AbG5uKz6E=
     = -2190
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    cout << c . Account ( "987654" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    987654:
       -500
     + 300, from: 123456, sign: XAbG5uKz6E=
     + 2890, from: 123456, sign: AbG5uKz6E=
     + 2890, from: 111111, sign: Okh6e+8rAiuT5=
     = 5580
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    cout << c . Account ( "111111" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    111111:
       5000
     - 2890, to: 987654, sign: Okh6e+8rAiuT5=
     = 2110
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    status = c . TrimAccount ( "987654" );
     // status = true
    strncpy ( debCpy, "111111", sizeof ( debCpy ) );
    strncpy ( credCpy, "987654", sizeof ( credCpy ) );
    strncpy ( signCpy, "asdf78wrnASDT3W", sizeof ( signCpy ) );
    status = c . Transaction ( debCpy, credCpy, 123, signCpy );
     // status = true
    cout << c . Account ( "987654" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    987654:
       5580
     + 123, from: 111111, sign: asdf78wrnASDT3W
     = 5703
    ---8<---8<---8<---8<---8<---8<---8<---
    */

    CBank e;
    status = e . NewAccount ( "123456", 1000 );
     // status = true
    status = e . NewAccount ( "987654", -500 );
     // status = true
    status = e . NewAccount ( "123456", 3000 );
     // status = false
    status = e . Transaction ( "123456", "666", 100, "123nr6dfqkwbv5" );
     // status = false
    status = e . Transaction ( "666", "123456", 100, "34dGD74JsdfKGH" );
     // status = false
    status = e . Transaction ( "123456", "123456", 100, "Juaw7Jasdkjb5" );
     // status = false
    balance = e . Account ( "666" ). Balance ( );
     // exception thrown
    cout << e . Account ( "666" );
     // exception thrown
    status = e . TrimAccount ( "666" );
     // status = false

    CBank g;
    status = g . NewAccount ( "123456", 1000 );
     // status = true
    status = g . NewAccount ( "987654", -500 );
     // status = true
    status = g . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
     // status = true
    status = g . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
     // status = true
    status = g . NewAccount ( "111111", 5000 );
     // status = true
    status = g . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" );
     // status = true
    CBank h ( g );
    status = g . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
     // status = true
    status = h . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" );
     // status = true
    status = g . NewAccount ( "99999999", 7000 );
     // status = true
    status = g . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" );
     // status = true
    status = g . TrimAccount ( "111111" );
     // status = true
    status = g . Transaction ( "123456", "111111", 221, "Q23wr234ER==" );
     // status = true
    cout << g . Account ( "111111" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    111111:
       -1802
     + 221, from: 123456, sign: Q23wr234ER==
     = -1581
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    cout << g . Account ( "99999999" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    99999999:
       7000
     + 3789, from: 111111, sign: aher5asdVsAD
     = 10789
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    cout << g . Account ( "987654" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    987654:
       -500
     + 300, from: 123456, sign: XAbG5uKz6E=
     + 2890, from: 123456, sign: AbG5uKz6E=
     + 2890, from: 111111, sign: Okh6e+8rAiuT5=
     + 123, from: 111111, sign: asdf78wrnASDT3W
     = 5703
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    cout << h . Account ( "111111" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    111111:
       5000
     - 2890, to: 987654, sign: Okh6e+8rAiuT5=
     - 789, to: 987654, sign: SGDFTYE3sdfsd3W
     = 1321
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    cout << h . Account ( "99999999" );
     // exception thrown
    cout << h . Account ( "987654" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    987654:
       -500
     + 300, from: 123456, sign: XAbG5uKz6E=
     + 2890, from: 123456, sign: AbG5uKz6E=
     + 2890, from: 111111, sign: Okh6e+8rAiuT5=
     + 789, from: 111111, sign: SGDFTYE3sdfsd3W
     = 6369
    ---8<---8<---8<---8<---8<---8<---8<---
    */

    CBank i;
    CBank j;
    status = i . NewAccount ( "123456", 1000 );
     // status = true
    status = i . NewAccount ( "987654", -500 );
     // status = true
    status = i . Transaction ( "123456", "987654", 300, "XAbG5uKz6E=" );
     // status = true
    status = i . Transaction ( "123456", "987654", 2890, "AbG5uKz6E=" );
     // status = true
    status = i . NewAccount ( "111111", 5000 );
     // status = true
    status = i . Transaction ( "111111", "987654", 2890, "Okh6e+8rAiuT5=" );
     // status = true
    j = i;
    status = i . Transaction ( "111111", "987654", 123, "asdf78wrnASDT3W" );
     // status = true
    status = j . Transaction ( "111111", "987654", 789, "SGDFTYE3sdfsd3W" );
     // status = true
    status = i . NewAccount ( "99999999", 7000 );
     // status = true
    status = i . Transaction ( "111111", "99999999", 3789, "aher5asdVsAD" );
     // status = true
    status = i . TrimAccount ( "111111" );
     // status = true
    cout << i . Account ( "111111" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    111111:
       -1802
     = -1802
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    cout << j . Account ( "111111" );
    /*
    ---8<---8<---8<---8<---8<---8<---8<---
    111111:
       5000
     - 2890, to: 987654, sign: Okh6e+8rAiuT5=
     - 789, to: 987654, sign: SGDFTYE3sdfsd3W
     = 1321
    ---8<---8<---8<---8<---8<---8<---8<---
    */
    
    return 0;
}
#endif /* __PROGTEST__ */