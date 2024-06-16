#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/cyw43_arch.h"

#define BUTTON_PIN 15
#define LED_PIN 16

volatile bool button_pressed = false;

void turn_on(){
    button_pressed = false;
    printf("\nInterrupt");
    gpio_put(LED_PIN, 1);
    sleep_ms(500);
    gpio_put(LED_PIN, 0);
}

void gpio_callback(uint gpio, uint32_t events){
    button_pressed = true;
}

int main(){
    stdio_init_all();
    cyw43_arch_init();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, 1);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, 0);
    gpio_pull_up(BUTTON_PIN);

    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    while(1){
        if (button_pressed == true){
            turn_on();
        }
        printf("\nHello!");
        sleep_ms(1000);
    }

    return 0;
}