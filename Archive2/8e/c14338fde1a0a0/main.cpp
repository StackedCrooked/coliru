#include "database.h"
#include <iostream>

using namespace best::manager;

void on_error(const std::string& msg) {
    std::cerr << "ERROR: " << msg << std::endl;
}

int main()
{
	DatabaseContext db;
	
	db.executeStatementAsynchronously(
		"INSERTT INTO `Test`",
		DatabaseContext::async_stmt_result_t(&on_error)
	);
	// ^ should result in an error message
	
	
	DatabaseContext::autoid_promise_t promisedAlarmId;
	DatabaseContext::autoid_future_t  futureAlarmId(promisedAlarmId.get_future());
	db.executeStatementAsynchronously(
		"INSERT INTO `Test`",
		DatabaseContext::async_stmt_result_t(0, promisedAlarmId)
	);
	std::cout << futureAlarmId.get() << std::endl;
	// ^ should result in a number
}
