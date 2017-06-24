/* MIT License                                                           */
/*                                                                       */
/* Copyright (c) 2016 David I. S. Mandala                                */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/ 
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*                                                                       */

#include <stdio.h>
#include <stdlib.h>
 
#include "libsoc_gpio.h"
#include "libsoc_debug.h"
#include "libsoc_board.h"


/* This bit of code below makes this example work on all 96Boards */
unsigned int GPIO_LED;
unsigned int GPIO_BUTTON;

int last_touch;
int led_state = 0;
int running = 1;

__attribute__((constructor)) static void _init()
{
    board_config *config = libsoc_board_init();
    GPIO_BUTTON = libsoc_board_gpio_id(config, "GPIO-A");
    GPIO_LED = libsoc_board_gpio_id(config, "GPIO-C");
   libsoc_board_free(config);
} 
/* End of 96Boards special code */
 
int main()
{
    gpio *gpio_led,*gpio_button;
    int touch;
    
    libsoc_set_debug(0);
    gpio_led = libsoc_gpio_request(GPIO_LED,LS_SHARED);
    gpio_button = libsoc_gpio_request(GPIO_BUTTON,LS_SHARED);
    
    if((gpio_led == NULL) || (gpio_button == NULL))
    {
        goto fail;
    }
    libsoc_gpio_set_direction(gpio_led,OUTPUT);
    libsoc_gpio_set_direction(gpio_button,INPUT);
    
    if((libsoc_gpio_get_direction(gpio_led) != OUTPUT) 
    || (libsoc_gpio_get_direction(gpio_button) != INPUT))   
    {
        goto fail;
    }
    while(running)
    {
        touch = libsoc_gpio_get_level(gpio_button);
        if(touch == 1 && last_touch == 0){
            led_state = led_state==1?0:1;
            libsoc_gpio_set_level(gpio_led,led_state);
            usleep(100000);
        }
        last_touch = touch;
        usleep(1);
    }    
    fail:
    if(gpio_led || gpio_button)
    {
        printf("apply gpio resource fail!\n");
        libsoc_gpio_free(gpio_led);
        libsoc_gpio_free(gpio_button);
    }
    return EXIT_SUCCESS;
}
