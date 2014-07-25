.h file

/*
 * Person.h
 *
 *  Created on: Jul 21, 2014
 *      Author: sstory
 */

#ifndef PERSON_H_
#define PERSON_H_
#include <string>
class Person {
private:
    std::string _Name;
	std::string _Address;
public:
	Person();
	Person(const std::string &Name,const std::string &Address);
	virtual ~Person();

	std::string toString(){
	//	return new std::string(_Name + " " + _Address);
	}
};

#endif /* PERSON_H_ */



.cpp file

/*
 * Person.cpp
 *
 *  Created on: Jul 21, 2014
 *      Author: sstory
 */

#include "Person.h"

Person::Person(){
    this->_Name="";
	this->_Address="";
}

Person::Person(std::string &Name,std::string &Address) {
	this->Person();
	this->_Name=Name;
	this->_Address=Address;
}

Person::~Person() {
	// TODO Auto-generated destructor stub
}

