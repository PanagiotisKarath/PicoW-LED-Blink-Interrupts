/*
* The necessary libraries are included.
* "hardware/gpio.h" is the library we use to implement
* the interrupt service routine (ISR)
*/
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/cyw43_arch.h"

/*
* We define the button pin as GPIO pin 15
* and the LED pin as GPIO pin 16
*/
#define BUTTON_PIN 15
#define LED_PIN 16

/*
* This boolean variable serves as a flag, which the ISR raises when it's called.
* It is volatile because it can change at any moment (because of the interrupt) and as such
* should always be read or written from the memory and not be cached.
*/
volatile bool button_pressed = false;

/*
* This function is called when the flag is raised. Inside the flag is lowered so it can be raised in future interrupts.
* This function is called inside the main function NOT inside the ISR
*/
void turn_on(){
    button_pressed = false; //boolean is made false
    printf("\nInterrupt"); //Prints "Interrupt" for easier I/O monitoring
    gpio_put(LED_PIN, 1); //LED is turned on
    sleep_ms(500); //Sleep for half a second
    gpio_put(LED_PIN, 0); //LED is turned off
}

/*
* This is the function called when an interrupt is triggered (ISR). In this case the only thing that happens if that
* the boolean variable is made true
*/
void gpio_callback(uint gpio, uint32_t events){
    button_pressed = true;
}

int main(){
    /*
    * Initializing all I/0 interfaces, as well as initializing the wireless chip
    */
    stdio_init_all();
    cyw43_arch_init();

    /*
    * The LED pin is initialized as output. Output can be initialized as "1" and input as "0"
    */
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, 1);

    /*
    * Here the button pin is initialized as input.
    * The third line is important to understand, because it configures the button pin 
    * to the Pull-up resistor. That means that by default the input is logic level 1.
    * When the button is pressed GPIO pin 15 is connected to the ground, it reads 
    * logic level 0 and this triggers a blink
    */
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, 0);
    gpio_pull_up(BUTTON_PIN);

    /*
    * Set up the GPIO interrupt on the button pin to trigger on the falling edge (transition from 1 to 0).
    * When the button is pressed, the gpio_callback function will be called
    */
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);


    /*
    * Infinite loop. While this loop is running the interrupt can be triggered
    */
    while(1){
        if (button_pressed == true){ //If the flag is up
            turn_on(); //The function to turn on the LED is called
        }
        printf("\nHello!"); //Prints "Hello!" to monitor interrupts easier
        sleep_ms(1000); //Prints every half a second
    }

    return 0; //The program will never reach this line but it's good practice to add
}