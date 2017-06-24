//g++ galiaSystem.cpp -o a -lsoc -g -Wall -lmraa

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <inttypes.h>
#include "libsoc_spi.h"
#include "libsoc_gpio.h"
#include "libsoc_debug.h"
#include "mraa.hpp"

#define GPIO_A 23
#define GPIO_B 24
#define GPIO_C 25
#define GPIO_D 26
#define GPIO_E 27
#define GPIO_F 28
#define GPIO_G 29
#define GPIO_H 30
#define GPIO_I 31
#define GPIO_J 32
#define GPIO_K 33
#define GPIO_L 34


#define ADC1_A0 0x80 // Luminosidade - A0
#define ADC1_A1 0x90 // Sensor Nivel de Agua - A1 
#define ADC2_A2 0xA0 // Sensor de Temperatura e Umidade - A2
#define ADC2_A3 0xB0 // Sensor de Umidade do solo - A3
 
#define GPIO_CS 18

static uint8_t tx[3],rx[3];
gpio *gpio_cs;
spi *spi_dev;

int getAnalogValue(int txValue)
{
	int varReturn = 0;
 
	tx[0] = 0x01;
	tx[1] = txValue;
	tx[2] = 0x00;

	libsoc_gpio_set_level(gpio_cs,HIGH);
	usleep(10);
	libsoc_gpio_set_level(gpio_cs,LOW);
	libsoc_spi_rw(spi_dev,tx,rx,3);
	libsoc_gpio_set_level(gpio_cs,HIGH);

    varReturn = (rx[1]<<8)&0b1100000000;
    varReturn |= (rx[2]&0xff);
	return varReturn;
}

void convertVoltsToCelcius(int &tempVolts, float &tempCelsius)
{
	float aux = tempVolts;
	aux *= 5.0;
	aux /= 1024.0;
 	tempCelsius = (aux - 0.5) * 100; 
}
 
void waterPlants(mraa::Gpio *gpio, int sec=10);
void waterPlants(mraa::Gpio *gpio, int sec)
{
    
    gpio->write(1);
    sleep(sec);
    gpio->write(0);
    sleep(1);
    
}

using namespace std;

int main() {
    mraa::Gpio* gpio;
    gpio = new mraa::Gpio(GPIO_A);
    gpio->dir(mraa::DIR_OUT);

    int lum = 0;
	int waterLevel = 0;
	int tempVolts = 0;
	int groundUmi = 0;
    float tempCelsius = 0;
    libsoc_set_debug(0);

    gpio_cs = libsoc_gpio_request(GPIO_CS,LS_SHARED);

    if(gpio_cs == NULL) {
    goto fail;
    }

    libsoc_gpio_set_direction(gpio_cs,OUTPUT);

    if(libsoc_gpio_get_direction(gpio_cs) != OUTPUT){
    printf("Failed to set direction to OUTPUT!\n");
    goto fail;  
    }
    
   spi_dev = libsoc_spi_init(0,0);   
     
   if(!spi_dev){
    printf("Failed to get spidev device!\n");
    return EXIT_FAILURE;
   }


   libsoc_spi_set_mode(spi_dev,MODE_0);
   libsoc_spi_get_mode(spi_dev);
   libsoc_spi_set_speed(spi_dev,10000);
   libsoc_spi_get_speed(spi_dev);
   libsoc_spi_set_bits_per_word(spi_dev,BITS_8);
   libsoc_spi_get_bits_per_word(spi_dev);
 

	while(1) 
	{
	    //waterPlants(gpio);
	    
		lum = getAnalogValue(ADC1_A0);
		printf("Luminosidade:%d\n",lum);
		
		waterLevel = getAnalogValue(ADC1_A1);
		printf("Water Level:%d\n", waterLevel);

		tempVolts = getAnalogValue(ADC2_A2);
		convertVoltsToCelcius(tempVolts, tempCelsius);
		printf("Temp: %f (°c)\n", tempCelsius);
		
		groundUmi = getAnalogValue(ADC2_A3);
		printf("GroundUmi:%d\n",groundUmi);



		sleep(1);
	}

   free:
   libsoc_spi_free(spi_dev);
   fail:
   if(gpio_cs) {
    libsoc_gpio_free(gpio_cs);
   }

   return EXIT_SUCCESS;
}
