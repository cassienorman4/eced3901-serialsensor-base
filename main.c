// Minimal R-Pi Pico USB File

#include <stdio.h>
#include "pico/stdlib.h"

#define PIN_LED PICO_DEFAULT_LED_PIN

int main() {
    stdio_init_all();
    stdio_set_translate_crlf(&stdio_usb, false);

    //WARNING: Default library needs flow control set to RTS/CTS - otherwise port will
    // not connect. The LED turns on once port is detected in firmware.
    while (!stdio_usb_connected());

    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);
    gpio_put(PIN_LED, 1);

    int adc = 22;

    while(1){
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
                printf("ADC: %d\n", adc);
                break;

            default:
                putchar('N');            
        }
    }

    return 0;
}

