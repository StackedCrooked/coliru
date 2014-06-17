
#include <exception>
#include <iostream>

// Library
namespace A {

struct Error {};

namespace Log {

void report_error(std::exception const&) {
    std::cerr << "[std::exception]\n";
}
void report_error(A::Error const&) {
	std::cerr << "[A::Error]\n";
}

// Used from within library
void report_error(std::exception_ptr eptr) {
	try {
		std::rethrow_exception(eptr);
	} catch (A::Error const& err) {
		Log::report_error(err);
	} catch (...) {
		std::cerr << "[unknown exception]\n";
	}
}

} // Log

} // A

// Application
namespace B {

// Different error type
struct Error {};

namespace Log {

// Namespace is more complicated, so ideally this would be used:
//using namespace A::Log;

// ... but then report_error() calls in B::Log::report_error(std::exception_ptr)
// can't find the declarations in the imported namespace.
// So I try this, but then the std::exception_ptr declarations conflict!

using A::Log::report_error;

void report_error(B::Error const&) {
	std::cerr << "[B::Error]\n";
}

void report_error(std::exception_ptr eptr) {
	try {
		std::rethrow_exception(eptr);
	} catch (A::Error const& err) {
		Log::report_error(err);
	} catch (B::Error const& err) {
		Log::report_error(err);
	} catch (...) {
		std::cerr << "[unknown exception]\n";
	}
}

} // Log

} // B

int main() {
	// Application mostly just wants to report any exception,
	// but there are branches where the application wants to handle
	// a specific error specially, but still wants to report the error.
	// It's more direct to call report_error(B::Error const&) in that
	// case, because you already have a ref to the object.
	// In any case, reducing it to just having report_error(std::exception_ptr)
	// is unideal, and {insert optimization pedantry here}.
	try {
		throw B::Error{};
	} catch (...) {
		B::Log::report_error(std::current_exception());
	}

	return 0;
}
