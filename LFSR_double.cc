#include <iostream>


uint64_t iState;



double Next(){
    uint64_t bit  = ((iState >> 2) ^(iState >> 6) ^(iState >> 7) ^ (iState >> 8) ^ (iState >> 10) ^ (iState >> 15) ) & 1;
    iState =  (iState >> 1) | (bit <<63);
    return (double)(iState)/3.689348815e19;
}

int main(){
    iState = 435235421;
    for(int i=0;i<100;++i){
        std::cout<<Next()<<std::endl;
    }
}