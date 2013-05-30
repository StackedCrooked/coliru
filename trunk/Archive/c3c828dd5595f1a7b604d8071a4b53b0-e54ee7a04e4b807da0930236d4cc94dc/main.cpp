#include <boost/any.hpp>
#include <boost/type_traits.hpp>

#include <map>
#include <cstring>
#include <iostream>

class ValueNotFoundException : public std::exception {
private:
    std::string error_message_;
public:
	ValueNotFoundException(const std::string &argMessage) :
		error_message_(argMessage) {
	}
	~ValueNotFoundException() throw() {
	}
	const char* what() const throw() {
		return error_message_.c_str();
	}
};

namespace EnumFooType {
typedef enum {
    UNDEFINED = 0,
	FOO_1 = 1,
	FOO_2 = 2	
} Type;
}

namespace ValueType {
typedef enum {
	UNDEFINED = 0,
	VAL_INT = 1,
	VAL_STR_1 = 2,
	VAL_STR_2 = 3
} Type;
}

template<class T>
class ValueHolder {
private:
	T value;
public:
	ValueHolder(const T &argValue) :
		value(argValue) {
	}
	const T& getValue() {
		return value;
	}
	~ValueHolder() {}
};

template<>
class ValueHolder<const char*> {
private:
	char* value;

public:
	ValueHolder(const char* argValue) {
		value = strdup(argValue);
		std::cout << "constructing ValueHolder(const char*) " << value << std::endl;
	}
	ValueHolder(const ValueHolder<const char*> &argExtension) {
		value = strdup(argExtension.value);
	}
	const char* getValue() const {
		std::cout << "returning ValueHolder(const char*) " << value << std::endl;
		return value;
	}
	~ValueHolder() {
		if(value != NULL)
			free(value);
	}
};

class ValueListHolder {
protected:
	std::map<ValueType::Type, boost::any> extensions_;

public:
	
	ValueListHolder() {}
	
	template<class Type>
	Type getExtension(const ValueType::Type &argValueType) const {
		std::map<ValueType::Type, boost::any>::const_iterator it = extensions_.find(argValueType);
		if(it != extensions_.end()) {
			switch(argValueType) {
			case ValueType::VAL_INT:
				if(boost::is_same<EnumFooType::Type, Type>::value) {
					return (boost::any_cast<ValueHolder<Type> >((*it).second)).getValue();
				} else {
					std::cout << "Wrong type for this value" << std::endl;
				}
				break;
			case ValueType::VAL_STR_1:
			case ValueType::VAL_STR_2:
				if(boost::is_same<const char *, typename boost::decay<Type>::type>::value) {
					return (boost::any_cast<ValueHolder<Type> >((*it).second)).getValue();
				} else {
					std::cout << "Wrong type value for this Holder" << std::endl;
				}
				break;
			default:
				std::cout << "Unhandled type of value, skipping..." << std::endl;
				break;
			}

		}
		throw ValueNotFoundException("Could not find a value for this subscriber extension");
	}
		template<class T>
	T getExtension(const ValueType::Type &argExtensionType, T argDefaultValue) const {
		try {
			return getExtension<T>(argExtensionType);
		} catch(ValueNotFoundException &e) {
			std::cout << "Exception caught, default value will be used!" << std::endl;
		}

		return argDefaultValue;
	}

	template<class T>
	void setExtension(const ValueType::Type &argExtensionType , T argExtensionValue) {
		boost::any any_value;
		switch(argExtensionType) {
		case ValueType::VAL_INT:
			if(boost::is_same<EnumFooType::Type, T>::value) {
				any_value = ValueHolder<T>(argExtensionValue);
				extensions_[argExtensionType] = any_value;
			} else {
				std::cout << "Wrong type value for Billing subscriber extension" << std::endl;
			}
			break;
		case ValueType::VAL_STR_1:
		case ValueType::VAL_STR_2:
			if(boost::is_same<const char *, typename boost::decay<T>::type>::value) {
				any_value = ValueHolder<T>(argExtensionValue);
				extensions_[argExtensionType] = any_value;
			} else {
				std::cout << "Wrong type for this value, it should be a cstring!" << std::endl;
			}
			break;
		default:
			std::cout << "Unhandled value type, skipping..." << std::endl;
			break;
		}
	}
};

int main() {
	ValueListHolder list_holder;

	list_holder.setExtension(ValueType::VAL_INT, EnumFooType::FOO_1);
	list_holder.setExtension(ValueType::VAL_STR_1, "FR");

	EnumFooType::Type tmp_enum_value = list_holder.getExtension(ValueType::VAL_INT, EnumFooType::UNDEFINED);

    if(tmp_enum_value != EnumFooType::FOO_1) {
        std::cout << "!!!ERROR!!! Wrong enum value!" << std::endl;
    } else {
        std::cout << "Good enum value :)" << std::endl;
    }

	const char* tmp_str = list_holder.getExtension(ValueType::VAL_STR_1, "");

	if(strcmp(tmp_str, "FR") != 0) {
		std::cout << "Value is " << tmp_str << " instead of FR" << std::endl;
	} else {
        std::cout << "Good str value :)" << std::endl;
    }

	return 0;
}