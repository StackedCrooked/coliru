  #include <iostream>

class Person
{
public:
  Person (int age, int weight)
  {
    m_age = age;
    m_weight = weight;
  }

  void showInfo()
  {
    std::cout << "I am " << m_age << " years old " ;
    std::cout << "and weighs " << m_weight << " kilo.\n\n" ;
  }

  virtual void getID() = 0;
  
  int getAge() { return m_age; }
  int getWeight() { return m_weight; }

private:
  int m_age;
  int m_weight;
};

class Employee : public Person
{
public:
  Employee (int age, int weight, int salary)
  {
    m_salary = salary;
  }

  void showInfo()
  {
    std::cout << "I am " << m_age << " years old " ;
    std::cout << "and weighs " << m_weight << " kilo " ;
    std::cout << "and earns " << m_salary << " dollar.\n\n" ;
  }

  int getSalary() { return m_salary; }

private:
  int m_salary;
};