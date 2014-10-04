const int M = 1000;
const int N = 100;

void someFunction(double** x){
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            x[i][j] += 10;
        }
    }
}

int main(){
    double** x = new double*[M];
    for(int n = 0; n < M; n++)
        x[n] = new double[N];
    double* phi = new double[M];
    double theta = 1.1;
    double R = 1;
    for(int n = 0; n < M; n++){
        for(int i = 0; i < N; i++){
            x[n][i] = phi[n] + R;
        //    y[n][i] = phi[n] + R;
        }
    }
    
    someFunction(x);
}