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