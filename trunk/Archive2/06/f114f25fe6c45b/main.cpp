#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace pie {
    class Schema {
    public:
        explicit Schema(std::string name_arg) : _name(std::move(name_arg)) {

        }

        std::string const& name() const {
            return _name;
        }

    private:
        std::string _name;
    };

    class Relation {
    public:
        Relation(Schema const& schema_arg, std::string name_arg)
            : _schema(&schema_arg), _name(std::move(name_arg)) {

        }

        Schema const& schema() const {
            return *_schema;
        }

        std::string const& name() const {
            return _name;
        }

    private:
        Schema const* _schema;
        std::string _name;
    };

    class Attribute {
    public:
        Attribute(Relation const& relation_arg, std::string name_arg)
            : _relation(&relation_arg), _name(name_arg) {

        }

        Relation const& relation() const {
            return *_relation;
        }

        std::string const& name() const {
            return _name;
        }

        std::size_t write(std::ostream& stream, std::size_t argument_number) const {
            stream << relation().schema().name() << '.' << relation().name() << '.' << name();
            return argument_number;
        }

    private:
        Relation const* _relation;
        std::string _name;
    };

    namespace detail {
        class Query {
        public:
            explicit Query(Relation const& relation_arg)
                : _relation(&relation_arg) {

            }

            Query& select() {
                return *this;
            }

            template<typename Expression, typename... Expressions>
            Query& select(Expression expression, Expressions&&... expressions) {
                selects.push_back(std::make_shared<ExpressionDerived<Expression>>(std::move(expression)));
                return select(std::forward<Expressions>(expressions)...);
            }

            Query& where() {
                return *this;
            }

            template<typename Expression, typename... Expressions>
            Query& where(Expression expression, Expressions&&... expressions) {
                wheres.push_back(std::make_shared<ExpressionDerived<Expression>>(std::move(expression)));
                return where(std::forward<Expressions>(expressions)...);
            }

            std::size_t write(std::ostream& stream, std::size_t argument_number) const {
                // TODO: Refactor this function into smaller functions.

                stream << "SELECT ";
                auto had_first_select = false;
                for (auto&& select : selects) {
                    if (had_first_select) {
                        stream << ", ";
                    }
                    had_first_select = true;

                    argument_number = select->write(stream, argument_number);
                }
                stream << '\n';

                stream << "FROM " << _relation->schema().name() << '.' << _relation->name();
                stream << '\n';

                if (wheres.size() > 0) {
                    stream << "WHERE (";
                    auto had_first_where = false;
                    for (auto&& where : wheres) {
                        if (had_first_where) {
                            stream << ") AND (";
                        }
                        had_first_where = true;

                        argument_number = where->write(stream, argument_number);
                    }
                    stream << ")\n";
                }

                return argument_number;
            }

        private:
            class ExpressionBase {
            public:
                virtual ~ExpressionBase() = default;

                virtual std::size_t write(std::ostream& stream, std::size_t argument_number) const = 0;

            private:
            };

            template<typename T>
            class ExpressionDerived : public ExpressionBase, private T {
            public:
                explicit ExpressionDerived(T base) : T(std::move(base)) {

                }

                virtual std::size_t write(std::ostream& stream, std::size_t argument_number) const override {
                    return T::write(stream, argument_number);
                }
            };

            Relation const* _relation;
            std::vector<std::shared_ptr<ExpressionBase>> selects;
            std::vector<std::shared_ptr<ExpressionBase>> wheres;
        };
    }

    inline detail::Query from(Relation const& relation) {
        return detail::Query(relation);
    }
}

#include <iostream>

using pie::from;

int main() {
    pie::Schema public_("public");
    pie::Relation users(public_, "users");
    pie::Attribute id(users, "id");
    pie::Attribute username(users, "username");
    pie::Attribute email_address(users, "email_address");

    auto query =
        from(users).
        where(id).
        where(username, email_address).
        select(id);

    query.write(std::cout, 0);
}
