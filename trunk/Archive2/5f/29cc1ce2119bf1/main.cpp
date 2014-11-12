    #include <iostream>
    bool some_conditions = true;

    bool foo( double & answer ){
        if (some_conditions) {
            answer = 42.0;
        } else {
            answer = 0.0;
        }
        return answer != 0.0;
    }

    void call_foo( double & answer ) {
        if ( foo( answer ) ) {
            std::cout << "foo() = " << answer << std::endl;
        } else {
            std::cout << "foo() is zero" << std::endl;
        }
    }

    int main() {
        double answer;
        call_foo( answer );
        some_conditions = !some_conditions;
        call_foo( answer );
        return 0;
    }
