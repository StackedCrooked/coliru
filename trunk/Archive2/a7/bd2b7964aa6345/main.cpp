#include <iostream>
struct GLFWwindow { };
class BC { };
  template <class T>
  class Controller : public BC{ //BC is just for using this class as a template parameter itself
    public:
    Controller(){}                    
    Controller(Controller &controller){
      controller_ = &controller;
    }

    static Controller& getInstance(Controller *controller = nullptr){
      static Controller instance(*controller);
      return instance;
    }   

    //This is the key move, where the concrete implementation is invoked.
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
      (static_cast<T *>(getInstance().controller_))->keyCallbackImpl(window, key, scancode, action, mods); 
    }

    //Stub to be overridden by the concrete input handler        
    void keyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods){}

    //This is the wrapped input handler
    Controller *controller_;   

  };
  
  class TestController : public Controller<TestController> {
      public:
      void keyCallbackImpl(GLFWwindow* window, int key, int scancode, int action, int mods){
          std::cout << "TestControllerImpl" << std::endl;
    }
  };
  
  int main(){
      TestController tc;
      Controller<TestController>::getInstance(&tc);
      
      Controller<TestController>::keyCallback(nullptr, 0, 0, 0, 0);
  }