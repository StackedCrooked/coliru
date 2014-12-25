    #include <iostream>
    #include <tuple>
    #include <functional>
    #include <memory>
    using namespace std;
    
    #include <type_traits>
    #include <utility>
    
    template <typename T> struct TD;
    
    
    struct UkaSapUser {
        virtual void on_message_to_aka(int msg) = 0;
    };
    
    struct UkaSapProvider {
        virtual void on_message_from_aka(int msg) = 0;
    };
    
    struct Uka : public UkaSapUser {
        void on_message_to_aka(int msg) {
            cout << "Sending RNTP to AKA" << endl;
        }
        void set_uka_sap_provider(UkaSapProvider* uka_sap_provider) {
            uka_sap_provider_ = uka_sap_provider;
        }
        UkaSapProvider* uka_sap_provider_;
    };
    
    struct UlakIcicApplication : public UkaSapProvider {
        UlakIcicApplication(UkaSapUser& uka_sap_user)
         : uka_sap_user_(uka_sap_user) {
        }
        void on_message_from_aka(int msg) {
            /* deliver to FFR algorithm */
        }
        
        UkaSapUser& uka_sap_user_;
    };
    
    int main() {
        Uka uka;
        UlakIcicApplication app(uka);
        uka.set_uka_sap_provider(&app);
    }