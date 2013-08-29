

#define BOOST_LIB_DIAGNOSTIC  // diagnostic linker activity
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Common API database Unit tests"

#include <boost/test/unit_test.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <sstream>
#include <stdint.h>
#include <map>
#include <exception>


/* Forward declarations */
class DatabaseParameters;
typedef boost::shared_ptr<DatabaseParameters> DatabaseParametersPtr_t;

/**
 * \enum	DatabaseManufacturer_t
 * \brief	Defines various types of database
 * manufacturer available
 */
namespace DatabaseManufacturer {
typedef enum {
	MYSQL,
	ORACLE,
	POSTGRESQL,
	ODBC,
	MONGODB,
	SQLITE3,
	UNDEFINED
} Type;

	inline const char* getStringFromDbManufacturer(DatabaseManufacturer::Type argManufacturer) {
		switch(argManufacturer) {
		case DatabaseManufacturer::MYSQL:
			return "MYSQL";
			break;
		case DatabaseManufacturer::ORACLE:
			return "ORACLE";
			break;
		case DatabaseManufacturer::POSTGRESQL:
			return "POSTGRESQL";
			break;
		case DatabaseManufacturer::ODBC:
			return "ODBC";
			break;
		case DatabaseManufacturer::MONGODB:
			return "MONGODB";
			break;
		case DatabaseManufacturer::SQLITE3:
			return "SQLITE3";
			break;
		default:
			break;
		}
		return "UNDEFINED";
	}

}

/**
 * \class	DatabaseParameters
 * \brief
 */
class DatabaseParameters {
protected:
	uint8_t id_;
	std::string host_;
	std::string user_;
	std::string passwd_;
	std::string db_name_;
	DatabaseManufacturer::Type manufacturer_;

public:
	DatabaseParameters() :
				id_(255),
				host_(""),
				user_(""),
				passwd_(""),
				db_name_(""),
				manufacturer_(DatabaseManufacturer::UNDEFINED) {
	}
	DatabaseParameters(
			uint8_t argId,
			std::string argHost,
			std::string argUser,
			std::string argPasswd,
			std::string argDbName,
			DatabaseManufacturer::Type argManufacturer,
			bool argIsDefault = false) :
				id_(argId),
				host_(argHost),
				user_(argUser),
				passwd_(argPasswd),
				db_name_(argDbName),
				manufacturer_(argManufacturer) {
	}
	virtual ~DatabaseParameters() {}
	virtual const uint8_t& getId() const {
		return id_;
	}
	virtual void setId(const uint8_t& argId) {
		id_ = argId;
	}
	virtual const std::string& getHost() const {
		return host_;
	}
	virtual void setHost(std::string argHost) {
		host_ = argHost;
	}
	virtual const std::string& getUser() const {
		return user_;
	}
	virtual void setUser(std::string argUser) {
		user_ = argUser;
	}
	virtual const std::string& getPasswd() const {
		return passwd_;
	}
	virtual void setPasswd(std::string argPasswd) {
		passwd_ = argPasswd;
	}
	virtual const std::string& getDbName() const {
		return db_name_;
	}
	virtual void setDbName(std::string argDbName) {
		db_name_ = argDbName;
	}
	virtual const DatabaseManufacturer::Type& getManufacturer() const {
		return manufacturer_;
	}
	virtual void setManufacturer(const DatabaseManufacturer::Type &argManufacturer) {
		manufacturer_ = argManufacturer;
	}
};

/**
 * \class	DatabaseParametersRegisteringException
 * \brief
 */
class DatabaseParametersLoadingException : public std::exception {
protected:
	std::string loading_error_;
	DatabaseParametersPtr_t db_params_;

	DatabaseParametersLoadingException();

public:
	DatabaseParametersLoadingException(const std::string &argLoadingError, DatabaseParametersPtr_t argDbParams) :
			db_params_(argDbParams) {
		std::stringstream ss;
		ss << "DatabaseParametersLoadingException: " << argLoadingError << std::endl;
		if(db_params_.get() != NULL) {
			ss << "Id:           " << (int)db_params_->getId() <<std::endl;
			ss << "Host:         " << db_params_->getHost() <<std::endl;
			ss << "User:         " << db_params_->getUser() <<std::endl;
			ss << "Passwd:       " << db_params_->getPasswd() <<std::endl;
			ss << "DbName:       " << db_params_->getDbName() <<std::endl;
			ss << "Manufacturer: " << DatabaseManufacturer::getStringFromDbManufacturer(db_params_->getManufacturer()) <<std::endl;
		}
		loading_error_ = ss.str();
	}
	virtual ~DatabaseParametersLoadingException() throw() {}

	virtual const char* what() const throw() {
		return loading_error_.c_str();
	}
};

/**
 * \class	DatabaseHandler
 * \brief	Global database handler
 */
class DatabaseHandler : boost::noncopyable {
protected:
	static std::map<uint8_t,DatabaseParametersPtr_t> db_parameters_;
	static std::map<DatabaseManufacturer::Type,DatabaseParametersPtr_t> db_manufacturer_default_;
	static DatabaseParametersPtr_t db_default_;
	static boost::mutex monitor_;
	DatabaseHandler();

public:
	/**
	 * \brief
	 */
	static bool pushDatabaseParameters(DatabaseParametersPtr_t argDbParams, bool argIsGlobalDefault = false, bool argIsManufacturerDefault = false) {
		boost::mutex::scoped_lock guard(monitor_);

		if(db_parameters_.find(argDbParams->getId()) != db_parameters_.end()) {
			throw DatabaseParametersLoadingException("DatabaseId already exists", argDbParams);
			return false;

		} else if(argIsGlobalDefault) {

			if(db_default_.get() == NULL && db_manufacturer_default_.find(argDbParams->getManufacturer()) == db_manufacturer_default_.end()) {
				db_default_ = argDbParams;
				db_manufacturer_default_.insert(std::pair<DatabaseManufacturer::Type,DatabaseParametersPtr_t>(argDbParams->getManufacturer(), argDbParams));
				db_parameters_.insert(std::pair<uint8_t,DatabaseParametersPtr_t>(argDbParams->getId(), argDbParams));
				return true;

			} else {
				throw DatabaseParametersLoadingException("Cannot set this database as the global default one (Either one is already set, "
						"or there is already a default database for this manufacturer) ", argDbParams);
				return false;
			}
		} else if(argIsManufacturerDefault) {

			if(db_manufacturer_default_.find(argDbParams->getManufacturer()) == db_manufacturer_default_.end()) {
				db_manufacturer_default_.insert(std::pair<DatabaseManufacturer::Type,DatabaseParametersPtr_t>(argDbParams->getManufacturer(), argDbParams));
				db_parameters_.insert(std::pair<uint8_t,DatabaseParametersPtr_t>(argDbParams->getId(), argDbParams));
				return true;
			} else {
				throw DatabaseParametersLoadingException("Cannot set this database as the global default one", argDbParams);
				return false;
			}
		}
		db_parameters_.insert(std::pair<uint8_t,DatabaseParametersPtr_t>(argDbParams->getManufacturer(), argDbParams));
		return true;
	}
	static DatabaseParametersPtr_t getGlobalDefaultDatabase() {
		return db_default_;
	}
	static DatabaseParametersPtr_t getManufacturerDefaultDatabase(DatabaseManufacturer::Type argManufacturer) {
		std::map<DatabaseManufacturer::Type,DatabaseParametersPtr_t>::iterator it = db_manufacturer_default_.find(argManufacturer);
		if(it != db_manufacturer_default_.end())
			return (*it).second;

		return DatabaseParametersPtr_t();
	}
	static DatabaseParametersPtr_t getDatabaseParametersById(uint8_t argId) {
		std::map<uint8_t,DatabaseParametersPtr_t>::iterator it = db_parameters_.find(argId);
		if(it != db_parameters_.end())
			return (*it).second;

		return DatabaseParametersPtr_t();
	}
	static const std::map<uint8_t,DatabaseParametersPtr_t>& getDatabaseParameters() {
		return db_parameters_;
	}
};

std::map<uint8_t,DatabaseParametersPtr_t> DatabaseHandler::db_parameters_;
std::map<DatabaseManufacturer::Type,DatabaseParametersPtr_t> DatabaseHandler::db_manufacturer_default_;
DatabaseParametersPtr_t DatabaseHandler::db_default_ = DatabaseParametersPtr_t();
boost::mutex DatabaseHandler::monitor_;


BOOST_AUTO_TEST_SUITE(common_database)

BOOST_AUTO_TEST_CASE(DatabaseHandlerTest) {

    DatabaseParametersPtr_t db_param1(new DatabaseParameters()),
			db_param2(new DatabaseParameters()),
			db_param3(new DatabaseParameters()),
			db_param4;
	bool value1 = false;
//	bool value2 = true;
	std::stringstream ss;

	db_param1->setId(1);
	db_param1->setHost("sql1");
	db_param1->setUser("root");
	db_param1->setPasswd("testpwd");
	db_param1->setDbName("db_test");
	db_param1->setManufacturer(DatabaseManufacturer::MYSQL);

	db_param2->setId(1);
	db_param2->setHost("sql2");
	db_param2->setUser("root");
	db_param2->setPasswd("testpwd");
	db_param2->setDbName("db_test");
	db_param2->setManufacturer(DatabaseManufacturer::MYSQL);

	db_param3->setId(3);
	db_param3->setHost("sql3");
	db_param3->setUser("root");
	db_param3->setPasswd("testpwd3");
	db_param3->setDbName("db_test3");
	db_param3->setManufacturer(DatabaseManufacturer::ODBC);


	try {
		value1 = DatabaseHandler::pushDatabaseParameters(db_param1, true);
	} catch(DatabaseParametersLoadingException &e) {
//		ss << "No exception should have been raised: " << e.what();
		std::cout << "No exception should have been raised: " << e.what();
		BOOST_ERROR(ss.str());
		ss.str("");
	}

	if(!value1)
		BOOST_ERROR("Error while loading global default database");

	value1 = false;

//	std::cout << "About to push param2" << std::endl;
	try {
		DatabaseHandler::pushDatabaseParameters(db_param2, true);
	} catch(DatabaseParametersLoadingException &e) {
		std::cout << "Exception raised: "<< e.what();
		value1 = true;
	}
//	std::cout << "Pushed param2" << std::endl;

	if(!value1)
		BOOST_ERROR("Exception should have been raised when "
				"pushing a database of the same id than the previous one!");

	db_param2->setId(2);
	value1 = false;

	try {
		DatabaseHandler::pushDatabaseParameters(db_param2, true);
	} catch(DatabaseParametersLoadingException &e) {
		value1 = true;
	}

	if(!value1)
		BOOST_ERROR("Exception should have been raised when pushing a global default "
				"database when one has already been pushed for the same!");

	db_param2->setManufacturer(DatabaseManufacturer::SQLITE3);
	value1 = false;

	try {
		BOOST_CHECK(DatabaseHandler::pushDatabaseParameters(db_param2, false, true) == true);
	} catch(DatabaseParametersLoadingException &e) {
		ss << "No exception should have been raised: " << e.what();
		BOOST_ERROR(ss.str());
		ss.str("");
	}

	try {
		BOOST_CHECK(DatabaseHandler::pushDatabaseParameters(db_param3) == true);
	} catch(DatabaseParametersLoadingException &e) {
		ss << "No exception should have been raised: " << e.what();
		BOOST_ERROR(ss.str());
		ss.str("");
	}

	db_param4 = DatabaseHandler::getGlobalDefaultDatabase();
	BOOST_CHECK(db_param4.get() != NULL && db_param4.get() == db_param1.get());

	db_param4 = DatabaseHandler::getManufacturerDefaultDatabase(db_param1->getManufacturer());
	BOOST_CHECK(db_param4.get() != NULL && db_param4.get() == db_param1.get());

	db_param4 = DatabaseHandler::getManufacturerDefaultDatabase(db_param2->getManufacturer());
	BOOST_CHECK(db_param4.get() != NULL && db_param4.get() == db_param2.get());

	db_param4 = DatabaseHandler::getDatabaseParametersById(db_param1->getId());
	BOOST_CHECK(db_param4.get() != NULL && db_param4.get() == db_param1.get());

	db_param4 = DatabaseHandler::getDatabaseParametersById(db_param2->getId());
	BOOST_CHECK(db_param4.get() != NULL && db_param4.get() == db_param2.get());

	db_param4 = DatabaseHandler::getDatabaseParametersById(db_param3->getId());
	BOOST_CHECK(db_param4.get() != NULL && db_param4.get() == db_param3.get());

	std::cout << "OK" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()