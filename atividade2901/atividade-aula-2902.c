#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_VERMELHO 11  // GPIO para o LED vermelho
#define LED_AMARELO 12   // GPIO para o LED amarelo
#define LED_VERDE 13     // GPIO para o LED verde

typedef enum {
    VERMELHO,
    AMARELO,
    VERDE
} EstadoSemaforo;

volatile EstadoSemaforo estado = VERMELHO; // Estado inicial

bool repeating_timer_callback(struct repeating_timer *t) {
    switch (estado) {
        case VERMELHO:
            gpio_put(LED_VERMELHO, 1);
            gpio_put(LED_AMARELO, 0);
            gpio_put(LED_VERDE, 0);
            printf("Semáforo: VERMELHO\n");
            estado = VERDE;
            break;
        case VERDE:
            gpio_put(LED_VERMELHO, 0);
            gpio_put(LED_AMARELO, 0);
            gpio_put(LED_VERDE, 1);
            printf("Semáforo: VERDE\n");
            estado = AMARELO;
            break;
        case AMARELO:
            gpio_put(LED_VERMELHO, 0);
            gpio_put(LED_AMARELO, 1);
            gpio_put(LED_VERDE, 0);
            printf("Semáforo: AMARELO\n");
            estado = VERMELHO;
            break;
    }
    return true;
}

int main() {
    stdio_init_all();

    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        sleep_ms(1000);
    }
}
