#include <string>
#include <vector>
#include <unordered_map>

    struct Identifier {
    	std::size_t hash;
		std::string name;
	};

	struct Primitive {
		Identifier id;
	};

	struct Type : public Primitive {
		std::size_t size;
	};

	struct EnumConstant : public Primitive {
		unsigned long long value;
	};

	struct Enum : public Type {
		std::vector<EnumConstant> constants;
	};

	struct Field : public Type {
		std::size_t offset;
	};

	struct Function : public Primitive {
		Type returnvalue;
		std::vector<std::pair<Identifier, Type>> parameters;
	};

	struct Class : public Type {
		std::unordered_map<std::string, std::size_t> enumnames;
		std::vector<Enum> enums;
		std::unordered_map<std::string, std::size_t> fieldnames;
		std::vector<Field> fields;
		std::unordered_map<std::string, std::size_t> functionnames;
		std::vector<Function> functions;
	};

	struct Namespace : public Primitive {
		std::unordered_map<std::string, std::size_t> enumnames;
		std::vector<Enum> enums;
		std::unordered_map<std::string, std::size_t> fieldnames;
		std::vector<Field> fields;
		std::unordered_map<std::string, std::size_t> functionnames;
		std::vector<Function> functions;
		std::unordered_map<std::string, std::size_t> classnames;
		std::vector<Class> classes;
		std::unordered_map<std::string, std::size_t> namespacenames;
		std::vector<Namespace> namespaces;
	};

int main() {
    // Yay!
    Namespace globalamespace;
    
    
}