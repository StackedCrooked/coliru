    #include <iostream>
    #include <limits>
     
    int main(){
            int myArray[4]={
                    5,10,15,20
            };
     
            std::cout<<"myArray with all elements:"<<std::endl;
            for(int c=0; c<4; c++){
                    std::cout<<myArray[c]<<std::endl;
            }
     
            int array1[2];
            int array2[2];
     
            array1[0] = myArray[0];
            array1[1] = myArray[1];
     
            array2[0] = myArray[2];
            array2[1] = myArray[3];
     
            if(
                    (array1[0] == myArray[0] && array1[1] == myArray[1])
                                                                    &&
                    (array2[0] == myArray[2] && array2[1] == myArray[3])
                    ){
                            myArray[0] = 0;
                            myArray[1] = 0;
                            myArray[2] = 0;
                            myArray[3] = 0;
            }
           
            std::cout<<std::endl;
     
            std::cout<<"Array 1 assigned with myArray first two elements: "<<std::endl;
            std::cout<<array1[0]<<std::endl;
            std::cout<<array1[1]<<std::endl;
     
            std::cout<<std::endl;
     
            std::cout<<"Array 2 assigned with myArray last two elements: "<<std::endl;
            std::cout<<array2[0]<<std::endl;
            std::cout<<array2[1]<<std::endl;
     
            std::cout<<std::endl;
     
            std::cout<<"myArray after having array1 & array2 assigned: "<<std::endl;
            for(int c=0; c<4; c++){
                    std::cout<<myArray[c]<<std::endl;
            }
     
            std::cin.sync();
            std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max()
            );
     
            return 0;
    }

