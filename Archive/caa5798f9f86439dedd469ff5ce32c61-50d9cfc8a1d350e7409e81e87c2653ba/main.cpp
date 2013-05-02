struct Joystick {};
struct Victor {};

class JoystickInput {
    public:
        static const int victor_count = 8;
        static const int button_count = 10;
        typedef Victor*(array_of_victor_pointers)[victor_count];
        
        JoystickInput(Joystick*){}
        JoystickInput(Joystick*, array_of_victor_pointers& vicArray);
        bool buttonClicked(int id){return true;}
        virtual void testForActions(){}
        
        Joystick * joystick;
        bool buttons [button_count];
        array_of_victor_pointers victors;
};

JoystickInput::JoystickInput(Joystick * joy, array_of_victor_pointers& vicArray) {
    joystick = joy;
    for (int x = 0; x < button_count; x++) {
        buttons[x] = false;
    }
    for (int n = 0; n < victor_count; n++) {
        victors[n] = vicArray[n];
    }
}

#include <iotream>
int main() {std::cout<<"compiles";}
