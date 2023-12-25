// spin.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a number of bytes to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spin spin.c -l bcm2835
// sudo ./spin
//
// Or you can test it before installing with:
// gcc -o spin -I ../../src ../../src/bcm2835.c spin.c
// sudo ./spin
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $
 
#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>
#include </usr/include/time.h>


 
int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
// Use for testing
//        bcm2835_set_debug(1);
    
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
 
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    //bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    uint32_t freq = 8000000;
    bcm2835_spi_set_speed_hz(freq);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
    
    // Send a some bytes to the slave and simultaneously read 
    // some bytes back from the slave
    // Most SPI devices expect one or 2 bytes of command, after which they will send back
    // some data. In such a case you will have the command bytes first in the buffer,
    // followed by as many 0 bytes as you expect returned data bytes. After the transfer, you 
    // Can the read the reply bytes from the buffer.
    // If you tie MISO to MOSI, you should read back what was sent.
    int samplemax= 10000000;
    int sample=0;
    double start, end; 
    char tbuf[] = { 0x01, 0x02 }; // Data to send
    char rbuf[] = {0x00, 0x00};
    struct timespec remaining,request = {20,20};

    start=time(NULL);
    while(sample<samplemax)
    {
        bcm2835_spi_transfernb(tbuf, rbuf, sizeof(tbuf));
        ++sample;
        //printf("sample = %d",sample);
        //usleep(0.1);
        
        //int response = nanosleep(&request,&remaining);
    }

    end=time(NULL);
    
    // buf will now be filled with the data that was read from the slave
    //printf("Read from SPI: %02X  %02X \n", rbuf[0], rbuf[1]);
       printf("# %d samples in %.1f seconds (%.0f/s)\n",
      sample, end-start, (float)sample/(end-start));

    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}