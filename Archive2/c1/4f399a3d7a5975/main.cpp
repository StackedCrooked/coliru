#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <string>
#include <iostream>

struct employee
{
    int         id_;
    std::string name_;
    std::string address_;

    employee(int id,std::string name,std::string address):id_(id),name_(name),address_(address) {}

};

struct id{};
struct name{};
struct address{};
struct id_hash{};
struct name_hash{};


typedef boost::multi_index_container<
    employee,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<boost::multi_index::tag<id>,  BOOST_MULTI_INDEX_MEMBER(employee,int,id_)>,
        boost::multi_index::ordered_unique<boost::multi_index::tag<name>,BOOST_MULTI_INDEX_MEMBER(employee,std::string,name_)>,
        boost::multi_index::ordered_unique<boost::multi_index::tag<address>, BOOST_MULTI_INDEX_MEMBER(employee,std::string,address_)>,
        boost::multi_index::hashed_unique<boost::multi_index::tag<id_hash>,  BOOST_MULTI_INDEX_MEMBER(employee,int,id_)>,
        boost::multi_index::hashed_unique<boost::multi_index::tag<name_hash>,  BOOST_MULTI_INDEX_MEMBER(employee,std::string,name_)>
    >
> employee_set;

typedef boost::multi_index::index<employee_set,id>::type employee_set_ordered_by_id_index_t;
typedef boost::multi_index::index<employee_set,name>::type employee_set_ordered_by_name_index_t;
typedef boost::multi_index::index<employee_set,name_hash>::type employee_set_hashed_by_name_index_t;

typedef boost::multi_index::index<employee_set,id>::type::const_iterator  employee_set_ordered_by_id_iterator_t;
typedef boost::multi_index::index<employee_set,name>::type::const_iterator  employee_set_ordered_by_name_iterator_t;


typedef boost::multi_index::index<employee_set,id_hash>::type::const_iterator  employee_set_hashed_by_id_iterator_t;
typedef boost::multi_index::index<employee_set,name_hash>::type::const_iterator  employee_set_hashed_by_name_iterator_t;


int main()
{
    employee_set employee_set_;

    employee_set_.insert(employee(1, "Employer1", "Address1"));
    employee_set_.insert(employee(2, "Employer2", "Address2"));
    employee_set_.insert(employee(3, "Employer3", "Address3"));
    employee_set_.insert(employee(4, "Employer4", "Address4"));

    // search by id using an ordered index 
    {
        const employee_set_ordered_by_id_index_t& index_id = boost::multi_index::get<id>(employee_set_);
        employee_set_ordered_by_id_iterator_t id_itr = index_id.find(2);
        if (id_itr != index_id.end() ) {
            const employee& tmp = *id_itr;
            std::cout << tmp.id_ << ", " << tmp.name_ << ", "  << tmp .address_ << std::endl;
        } else {
            std::cout << "No records have been found\n";
        }
    }

    // search by non existing id using an ordered index 
    {
        const employee_set_ordered_by_id_index_t& index_id = boost::multi_index::get<id>(employee_set_);
        employee_set_ordered_by_id_iterator_t id_itr = index_id.find(2234);
        if (id_itr != index_id.end() ) {
            const employee& tmp = *id_itr;
            std::cout << tmp.id_ << ", " << tmp.name_ << ", "  << tmp .address_ << std::endl;
        } else {
            std::cout << "No records have been found\n";
        }
    }

    // search by name using an ordered index
    {
        const employee_set_ordered_by_name_index_t& index_name = boost::multi_index::get<name>(employee_set_);
        employee_set_ordered_by_name_iterator_t name_itr = index_name.find("Employer3");
        if (name_itr != index_name.end() ) {
            const employee& tmp = *name_itr;
            std::cout << tmp.id_ << ", " << tmp.name_ << ", "  << tmp .address_ << std::endl;
        } else {
            std::cout << "No records have been found\n";
        }
    }

    // search by name using an hashed index
    {
        employee_set_hashed_by_name_index_t& index_name = boost::multi_index::get<name_hash>(employee_set_);
        employee_set_hashed_by_name_iterator_t name_itr = index_name.find("Employer4");
        if (name_itr != index_name.end() ) {
            const employee& tmp = *name_itr;
            std::cout << tmp.id_ << ", " << tmp.name_ << ", "  << tmp .address_ << std::endl;
        } else {
            std::cout << "No records have been found\n";
        }
    }

    // search by name using an hashed index but the name does not exists in the container
    {
        employee_set_hashed_by_name_index_t& index_name = boost::multi_index::get<name_hash>(employee_set_);
        employee_set_hashed_by_name_iterator_t name_itr = index_name.find("Employer46545");
        if (name_itr != index_name.end() ) {
            const employee& tmp = *name_itr;
            std::cout << tmp.id_ << ", " << tmp.name_ << ", "  << tmp .address_ << std::endl;
        } else {
            std::cout << "No records have been found\n";
        }
    }

    return 0;
}