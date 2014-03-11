#include <iostream>
#include <pthread.h>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (auto& el : vec) { os << el << ' '; }
    return os;
}

#define num 2
pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;

int arr[]={10,9,23,45,78,11,89,45,92,5,23,76,34,21,59,76};

void* odd_even(void* data)
{
    int a=*((int*)data);
    volatile bool sorted=false;
    unsigned int arr_length = sizeof(arr)/sizeof(arr[0]);
    pthread_mutex_lock(&mutex1);
    while(!sorted) {
        if (a==0) {
            sorted=true;
            for(unsigned int i=0; i < arr_length-2; i+=2) {
                if(arr[i] > arr[i+2]){
                    std::swap(arr[i], arr[i+2]);
                    sorted=false;
                }
            }
        }
        else if (a==1) {
            sorted=true;
            for(unsigned int i=1; i < arr_length-2; i+=2){
                if(arr[i] > arr[i+2]){
                    std::swap(arr[i], arr[i+2]);
                    sorted=false;
                }
            }
        }
    }//end while
    pthread_mutex_unlock(&mutex1);
    pthread_exit(NULL);
    return nullptr;
}

int main()
{    
    int a[]={0,1,2};
    pthread_t pth[num];

    for(int i=0;i<num;i++){
        int thread_id=pthread_create(&pth[i],NULL,odd_even,(void*)&a[i]);
        if(thread_id){
            std::cout << "Thread creation fail" << std::endl;
            return 1;
        }        
    }

    for(int j=0;j<num;j++)
        pthread_join(pth[j],NULL);

    std::vector<int> v(arr, arr+sizeof(arr)/sizeof(arr[0]));
    std::cout << v << std::endl;

    pthread_exit(NULL);
}
