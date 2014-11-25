    #include <iostream>
    #include <vector>
    
using namespace std;

class Matrix
{
public:
    Matrix() {};

    int M;
    int N;
    std::vector<double> data;


    int get(int i, int j){
        return data[i*N+j];
    }

    Matrix(int sizeR, int sizeC,double * input_data)
    {
        M=sizeR;//Rows
        N=sizeC;//Columns

        data.resize(M*N);//creation of 1D array, uses m&n values

        cout<<"\nMatrix::Matrix(int sizeR, int sizeC, double * input_data) is invoked\n\n";


        //ENTER DATA INTO MATRIX HERE:

        for(int i=0;i<M*N;i++)//Loops for every data entry into 1D array, uses r&c as referenece to size
            data[i] = input_data[i];//Accesses each value at specific location, inputs value 'val'

        for(int i=0;i<M*N;i++)//Loops for every data entry into 1D array
            cout<<data[i]<<" ";

    }


    //DECONSTRUCTOR
    ~Matrix(){
        cout<<"\n\nMatrix::~Matrix() is invoked\n\n";
    }

};

int main()
{
    int sizeR, sizeC, g1, g2;

    g1 = 2;
    g2 = 2;

    Matrix M1;

    cout<<"Enter No. Rows: ";
    cin>>sizeR;

    cout<<"Enter No. Columns: ";
    cin>>sizeC;

    double * input_data;
    input_data = new double[sizeR*sizeC];


    //INPUTS VALUES TO ARRAY
    for(int i=0;i<sizeR*sizeC;i++)//Loops for every row
        input_data[i] = i+1*input_data[i-1];

    Matrix(sizeR, sizeC, input_data);

    cout<<"Find value at row: ";
    cin>>sizeR;
    cout<<"Find value at column: ";
    cin>>sizeC;

    M1.get(g1, g2);


}