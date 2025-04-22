


#include <xc.h>

void main(void) {
    int i, sum;
    int num[]={1,2,3,4,5};
    sum=0;
    for(i=0; i<5; i++)
    {
        sum=sum+num[i];
    }
    TRISA=0;
    LATA=0;
    PORTA=sum;
    return;
}
