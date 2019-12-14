#include <iostream>
#include "Random.h"
#include <ctime>
#include <stdlib.h>

namespace Garfield{
    void P(){
    double t;
    double f = RndmUniform();
    int fi=0;
    for(int i=0;i<1000000000;i++){
        t = RndmUniform();
        if(f!=t){
            fi++;
        }
        else{
            std::cout<<f<<" " << fi<<std::endl;
            f=0.0;
        }
    }
    }

    void G(){
    double t;
    //srand48(234953453);
    double f = drand48();
    int fi = 0;
    for(int i=0;i<1000000000;i++){
        t = drand48();
        if(f!=t){
            fi++;
        }
        else{
            std::cout<<f<<" " << fi<<std::endl;
            f=0.0;
        }
    }
    }
}
int main(){
    clock_t time_req;
	// Using pow function
	time_req = clock();
    Garfield::P();
    time_req = clock() - time_req;
    std::cout<< "1 000 000 000 random numbers (TRANDOM) took "<<(float)time_req/CLOCKS_PER_SEC<<" Seconds"<<std::endl;
    time_req = clock();
    Garfield::G();
    time_req = clock() - time_req;
    std::cout<< "1 000 000 000 random numbers (drand) took "<<(float)time_req/CLOCKS_PER_SEC<<" Seconds"<<std::endl;

    return 0;
}