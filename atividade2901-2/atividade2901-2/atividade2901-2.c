#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos
#define LED_AZUL_PIN 11
#define LED_VERMELHO_PIN 12
#define LED_VERDE_PIN 13
#define BOTAO_PIN 5

// Estado do sistema
volatile bool em_execucao = false; // Impede múltiplos acionamentos do botão
volatile int estado_led = 0;        // Controla qual LED está sendo desligado

// Callback para desligar LEDs sequencialmente
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    if (estado_led == 0) {
        gpio_put(LED_AZUL_PIN, 0);
        estado_led++;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);  // Agendar próximo LED
    } else if (estado_led == 1) {
        gpio_put(LED_VERMELHO_PIN, 0);
        estado_led++;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);  // Agendar próximo LED
    } else if (estado_led == 2) {
        gpio_put(LED_VERDE_PIN, 0);
        estado_led = 0;
        em_execucao = false; // Permite nova ativação pelo botão
    }
    return 0;
}

// Callback do botão
void botao_press_callback(uint gpio, uint32_t events) {
    if (!em_execucao) {  // Só inicia se nenhum LED estiver apagando
        em_execucao = true;

        // Liga todos os LEDs
        gpio_put(LED_AZUL_PIN, 1);
        gpio_put(LED_VERMELHO_PIN, 1);
        gpio_put(LED_VERDE_PIN, 1);

        estado_led = 0;  // Reseta estado para iniciar sequência de desligamento
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();

    // Configuração dos LEDs
    gpio_init(LED_AZUL_PIN);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    gpio_init(LED_VERDE_PIN);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);

    // Configuração do botão
    gpio_init(BOTAO_PIN);
    gpio_set_dir(BOTAO_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_PIN);

    // Configuração da interrupção do botão
    gpio_set_irq_enabled_with_callback(BOTAO_PIN, GPIO_IRQ_EDGE_FALL, true, botao_press_callback);

    while (true) {
        sleep_ms(100);
    }

    return 0;
}
