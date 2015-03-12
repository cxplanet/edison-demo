/* Blink example using mraa */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>

#include "mraa.h"

#define LED_PIN 13

int running = 0;

void sig_handler(int signo)
{
    if ( signo == SIGINT ) {
        printf("Interrupt signal recieved, exiting...\n", LED_PIN);
        running = -1;
    }
}

int main()
{
    /* Initialize mraa */
    mraa_result_t r = MRAA_SUCCESS;
    mraa_init();

    /* Create access to GPIO pin */
    mraa_gpio_context gpio;
    gpio = mraa_gpio_init(LED_PIN);
    if ( gpio == NULL ) {
        fprintf(stderr, "Error opening GPIO\n");
        exit(1);
    }

    /* Set GPIO to output */
    r = mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
    if ( r != MRAA_SUCCESS ) {
        mraa_result_print(r);
    }

    /* Register an interrupt signal handler */
    signal(SIGINT, sig_handler);

    /* Turn LED off and on forever until SIGINT (Ctrl+c) */
    while ( running == 0 ) {

        r = mraa_gpio_write(gpio, 0);
        if ( r != MRAA_SUCCESS ) {
            mraa_result_print(r);
        }
        sleep(1);

        r = mraa_gpio_write(gpio, 1);
        if ( r != MRAA_SUCCESS ) {
            mraa_result_print(r);
        }
        sleep(1);
    }

    /* Clean up GPIO and exit */
    r = mraa_gpio_close(gpio);
    if ( r != MRAA_SUCCESS ) {
        mraa_result_print(r);
    }

    return r;
}

