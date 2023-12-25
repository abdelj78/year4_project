#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>
#include </usr/include/time.h>

#define samplemax 2000000

//int samplemax= 2000000;

char rbuf[] = {0x02, 0x0A};

uint16_t values[samplemax];



int main(int argc, char **argv)
{
    printf("rbuf[0] = %0x\n",rbuf[0]);
    printf("rbuf[1] = %0x\n",rbuf[1]);
    values[0] = (((uint16_t)rbuf[1])<<8) | ((uint16_t)rbuf[0]);

    printf("%04x\n", values[0]);
    printf("decimal = %d\n", values[0]);
    printf("%2x\n",rbuf[0]);
    
    return 0;
}