/*
 *          File: employee.cpp
 *        Author: Robert I. Pitts <rip@cs.bu.edu>
 * Last Modified: April 8, 2000
 *         Topic: Introduction to Inheritance in C++
 * ----------------------------------------------------------------
 *
 * Employee method definitions.
 */

#include "employee.h"

Employee::Employee(string theName, float thePayRate)
{
  name = theName;
  payRate = thePayRate;
}

string Employee::getName() const
{
  return name;
}

float Employee::getPayRate() const
{
  return payRate;
}

float Employee::pay(float hoursWorked) const
{
  return hoursWorked * payRate;
}