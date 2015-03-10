// This should compile in Coliru and the like; if we were to put these in
// separate files on a local machine, we'd omit this macro.
#define SINGLE_FILE


////////////////////////////////////////////////////////////////////////////////
// Introvert.hpp
////////////////////////////////////////////////////////////////////////////////
#ifndef INTROVERT_HPP
#define INTROVERT_HPP


// This class has interfaces that are not public but are made available to
// certain friends without making its private members available to those friends
// (i.e. they're not direct friends of this class in general, just friends of
// the interfaces).
class Introvert {
    
    // A collection of functions given only to certain friends.
    // How to call: [Introvert instance].friendship.[function]
    private:
    class Friendship_Interface {
        // Here list friends that can use this interface:
        friend class IntrovertFriend;
        
        // Here are the functions:
        const char* getName();
        void setName(const char*);
        
        // We need to construct an instance of this class for each instance of
        // the containing class and we need access to the containing instance.
        friend class Introvert;
        Friendship_Interface(Introvert* outer) : m_outer(outer) {};
        Introvert* m_outer; // non-owning observer
    };
    public:
    Friendship_Interface friendship;
    // C++11: Friendship_Interface friendship{this};
    
    
    // A specific function (object) given only to certain friends.
    // How to call: [Introvert instance].getName()
    private:
    class GetName_Interface {
        // Here list friends that can use this function:
        friend class IntrovertFriend;
        
        // The instance will act as a function object.
        const char* operator()();
        
        // We need to construct an instance of this class for each instance of
        // the containing class and we need access to the containing instance.
        friend class Introvert;
        GetName_Interface(Introvert* outer) : m_outer(outer) {};
        Introvert* m_outer; // non-owning observer
    };
    public:
    GetName_Interface getName;
    // C++11: GetName_Interface getName{this};
    
    // A specific function (object) given only to certain friends.
    // How to call: [Introvert instance].setName([string]);
    private:
    class SetName_Interface {
        // Here list friends that can use this function:
        friend class IntrovertFriend;
        
        // The instance will act as a function object.
        void operator()(const char*);
        
        // We need to construct an instance of this class for each instance of
        // the containing class and we need access to the containing instance.
        friend class Introvert;
        SetName_Interface(Introvert* outer) : m_outer(outer) {};
        Introvert* m_outer; // non-owning observer
    };
    public:
    SetName_Interface setName;
    // C++11: SetName_Interface setName{this};
    
    
    // Constructor for the outer class
    public:
    Introvert(const char* name);
    
    
    // If we want to have multiple friend interfaces that use some of the same
    // functions, those should be private members of the outer class that the
    // friend interfaces' functions merely wrap -- this avoids code duplication.
    private:
    const char* getName_Implementation();
    void setName_Implementation(const char*);
    
    
    // Data members for the outer class
    // -- The cool thing is these stay truly private!
    private:
    const char* m_name;
};

#endif //ifndef INTROVERT_HPP


////////////////////////////////////////////////////////////////////////////////
// Introvert.cpp
////////////////////////////////////////////////////////////////////////////////
#ifndef SINGLE_FILE
#   include "Introvert.hpp"
#endif //ifndef SINGLE_FILE


// This function is not public, but may be wrapped by the friendship interfaces.
const char* Introvert::getName_Implementation() {
    return m_name;
}

// This function is not public, but may be wrapped by the friendship interfaces.
void Introvert::setName_Implementation(const char* name) {
    m_name = name;
}


// This is filtered through a limited friendship interface:
// [Introvert instance].friendship.getName()
const char* Introvert::Friendship_Interface::getName() {
    // We could do this:
    //return m_outer->m_name;
    // But, to avoid code duplication with multiple interfaces wrapping that
    // functionality, we should do this:
    return m_outer->getName_Implementation();
}

// This is filtered through a limited friendship interface:
// [Introvert instance].friendship.setName([string])
void Introvert::Friendship_Interface::setName(const char* name) {
    // We could do this:
    //m_outer->m_name = name;
    // But, to avoid code duplication with multiple interfaces wrapping that
    // functionality, we should do this:
    m_outer->setName_Implementation(name);
}


// This is technically a function object with friendship:
// [Introvert instance].getName()
const char* Introvert::GetName_Interface::operator()() {
    // We could do this:
    //return m_outer->m_name;
    // But, to avoid code duplication with multiple interfaces wrapping that
    // functionality, we should do this:
    return m_outer->getName_Implementation();
}

// This is technically a function object with friendship:
// [Introvert instance].setName([string])
void Introvert::SetName_Interface::operator()(const char* name) {
    // We could do this:
    //m_outer->m_name = name;
    // But, to avoid code duplication with multiple interfaces wrapping that
    // functionality, we should do this:
    m_outer->setName_Implementation(name);
}


// Outer class constructor:
Introvert::Introvert(const char* name)
: friendship(this) // not needed in C++11
, getName(this) // not needed in C++11
, setName(this) // not needed in C++11
, m_name(name)
{
}


////////////////////////////////////////////////////////////////////////////////
// IntrovertFriend.hpp
////////////////////////////////////////////////////////////////////////////////
#ifndef INTROVERTFRIEND_HPP
#define INTROVERTFRIEND_HPP

#ifndef SINGLE_FILE
#   include "Introvert.hpp"
#endif //ifndef SINGLE_FILE


// This class can access the interfaces of which it is a friend.
class IntrovertFriend {
    public:
    // Just a single demonstration function that doesn't even need an instance.
    static void testFriendship(Introvert friend_to_test);
};

#endif //ifndef INTROVERTFRIEND_HPP


////////////////////////////////////////////////////////////////////////////////
// IntrovertFriend.cpp
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#ifndef SINGLE_FILE
#   include "IntrovertFriend.hpp"
#endif //ifndef SINGLE_FILE


// Because IntrovertFriend is declared as a friend of
// Introvert::Friendship_Interface, it can access
// friend_to_test.friendship.[functions]
// Because IntrovertFriend is declared as a friend of
// Introvert::GetName_Interface and Introvert::GetName_Interface, it can access
// friend_to_test.getName() and friend_to_test.setName([string])
void IntrovertFriend::testFriendship(Introvert friend_to_test) {
    // 'const char* Introvert::m_name' is private
    //friend_to_test.m_name = "Willy";
    
    // 'class Introvert::Friendship_Interface' is private
    //Introvert::Friendship_Interface bogey(&friend_to_test);
    
    std::cout<<friend_to_test.getName()<<'\n';
    
               friend_to_test.setName("Bill");
    std::cout<<friend_to_test.getName()<<'\n';
    
               friend_to_test.friendship.setName("Joe");
    std::cout<<friend_to_test.friendship.getName()<<std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// main.cpp
////////////////////////////////////////////////////////////////////////////////
#ifndef SINGLE_FILE
#   include "Introvert.hpp"
#   include "IntrovertFriend.hpp"
#endif //ifndef SINGLE_FILE


// Demonstrate that the friend interfaces work correctly.
int main() {
    Introvert lonely_guy("John");
    
    // 'const char* Introvert::m_name' is private
    //lonely_guy.m_name = "Phil";
    
    // 'void Introvert::SetName_Interface::operator()(const char*)' is private
    //lonely_guy.setName("Steve");
    
    // 'void Introvert::Friendship_Interface::setName(const char*)' is private
    //lonely_guy.friendship.setName("Bob");
    
    // 'class Introvert::Friendship_Interface' is private
    //Introvert::Friendship_Interface bogey(&lonely_guy);
    
    IntrovertFriend::testFriendship(lonely_guy);
}
