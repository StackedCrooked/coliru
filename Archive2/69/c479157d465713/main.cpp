#include <iostream>
#include <pthread.h>
 
class Cluster
{
    public:
    int x;
    static void *_staticTimeEffects(void *context){
        reinterpret_cast<Cluster*>(context)->x += 10;
        return 0;
    }
};

int main()
{
    const int numberOfClusters = 5;
    Cluster** clusterArray = new Cluster*[5];
    for (int i = 0; i < numberOfClusters; i++) {
        clusterArray[i] = new Cluster;
        clusterArray[i]->x = i;
    }
    
    
    pthread_t threads[numberOfClusters];    													//threaded
    for(int i = 0; i < numberOfClusters ; i++) {
        pthread_create(&(threads[i]), NULL, &(Cluster::_staticTimeEffects), clusterArray[i]);   //threaded
        //Cluster::_staticTimeEffects(clusterArray[i]);									        //unthreaded
    }
    for(int i = 0; i < numberOfClusters ; i++){ 												//threaded
        pthread_join(threads[i], NULL);															//threaded
    }																							//threaded
    
    
    // Should output 10 11 12 13 14
    for(int i = 0; i < numberOfClusters; i++) {
        std::cout << clusterArray[i]->x << ' ';
        delete clusterArray[i];
    }
}
