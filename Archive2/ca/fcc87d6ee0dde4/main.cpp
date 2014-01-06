class any{
    protected:
        template<class T> struct variable{
        public:
            T val;
            template<class NewT> void setType(){
                T = NewT;
            }
        };
        variable<int> v;
    public:
        any(){
            v.val = 0;
        }
        template<class T> any(T V){
            if (T != decltype(v.val)){
                v.setType<T>();
                v.val = V;
            }
            else{
                v.val = V;
            }
        }
        ~any(){
            delete &v;
        }
        decltype(v.val) value(){ // <<<<< Error here >>>>>
            return v.val;
        }
        template<class T> static any create(T V){
            return any(V);
        }
    };