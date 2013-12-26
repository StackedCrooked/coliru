

template<int N>
struct Data
{
    char data[N];
};


template<int N>
Data<N> get_data();

template<int N>
void set_data(Data<N>);


int main()
{    
    set_data(get_data<LENGTH>());
}