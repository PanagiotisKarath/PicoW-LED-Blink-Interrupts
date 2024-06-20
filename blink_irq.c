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
* This is the function called when an interrupt is triggered (ISR). In this case turning the LED on (and off)
* happens inside the interrupt service routine. The LED does not really blink, rather its state gets toggled 
* each time the button is pressed
*/
void gpio_callback(uint gpio, uint32_t events){
    printf("\nInterrupt"); //It prints the word "Interrupt" so I know that the function is called even if the LED has a problem
    if(gpio_get(LED_PIN) == 0){ //If the LED is off
        gpio_put(LED_PIN, 1); //Turn it on
    }
    else { //Else if the LED is on
        gpio_put(LED_PIN, 0); //Turn it off
    }
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
        printf("\nHello!"); //I chose to print "Hello!" so that when interrupt gets triggered it's clearer in the console output 
        sleep_ms(1000); //Print happens every one second
    }

    return 0; //The program will never reach this line but it's good practice to add
}