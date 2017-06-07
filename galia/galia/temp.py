from gpio_96boards import GPIO
import time


def waterPlants(sec = 10):
    releID = GPIO.gpio_id('GPIO_A')
    rele = ((releID, 'out'),)
    with GPIO(rele) as gpio:
	    gpio.digital_write(releID, GPIO.HIGH)
	    time.sleep(sec)
	    gpio.digital_write(releID, GPIO.LOW)
	

