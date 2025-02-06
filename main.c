// Minimal R-Pi Pico USB File

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define PIN_LED PICO_DEFAULT_LED_PIN

int main() {
    stdio_init_all();
    stdio_set_translate_crlf(&stdio_usb, false);
    //initialize the ADC module:
    printf("ADC Example, measuring GPIO26\n");
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);
    //read and adc value
    const float conversion_factor = 3.3f / (1<<12);


  


    //WARNING: Default library needs flow control set to RTS/CTS - otherwise port will
    // not connect. The LED turns on once port is detected in firmware.
    while (!stdio_usb_connected());

    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);
    gpio_put(PIN_LED, 1);
    

    while(1){
        uint16_t result= adc_read();
        char command = getchar();

        switch(command){
            case '?':
                putchar('A');
                break;
            case 'L':
                gpio_put(PIN_LED, 0);
                break;
            case 'l':
                gpio_put(PIN_LED, 1);
                break;
            case 'S':
                printf("ADC: %d\n", result);
                break;

            default:
                putchar('N');            
        }
    }

    return 0;
}

