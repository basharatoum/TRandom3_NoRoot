#include <iostream>
#include "Random.h"
#include <ctime>
#include <stdlib.h>
#include "XorShift256.h"


namespace Garfield{
    void P(){
        //TRANDOM3
    double t;
    double f = RndmUniform();
    int fi=0;
    for(int i=0;i<100000000;i++){
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
        //DRAND48
    double t;
    //srand48(234953453);
    double f = drand48();
    int fi = 0;
    for(int i=0;i<100000000;i++){
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
//extern uint64_t s[4] = {32452345,3453452123,4545645,2342314};
int main(){
    clock_t time_req;
	// Using pow function
	time_req = clock();
    Garfield::P();
    time_req = clock() - time_req;
    std::cout<< "100 000 000 random numbers (TRANDOM) took "<<(float)time_req/CLOCKS_PER_SEC<<" Seconds"<<std::endl;
    time_req = clock();
    Garfield::G();
    time_req = clock() - time_req;
    std::cout<< "100 000 000 random numbers (drand) took "<<(float)time_req/CLOCKS_PER_SEC<<" Seconds"<<std::endl;
    

    //XORSHIFT 256+
    time_req = clock();
    double aa  = next();
    double f = aa;
    int fi=0;
    for(int i=0;i<100000000;++i){
        double a  = next();
    }
    
    time_req = clock() - time_req;
    std::cout<< "100 000 000 random numbers (XorShitft256) took "<<(float)time_req/CLOCKS_PER_SEC<<" Seconds"<<std::endl;
    
    return 0;
}