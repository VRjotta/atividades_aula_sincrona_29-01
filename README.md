### atividades_aula_sincrona_29-01
##atividades da aula sincrona do dia 29 de janeiro.

# Projeto: Temporização e Controle de LEDs com Raspberry Pi Pico W

## Descrição
Este projeto implementa dois sistemas utilizando o microcontrolador Raspberry Pi Pico W no simulador Wokwi e ambiente de desenvolvimento VS Code. O primeiro sistema simula um semáforo com temporização de 3 segundos entre cada mudança de cor. O segundo sistema utiliza um temporizador de um disparo (One Shot) para controlar LEDs através de um botão (pushbutton).

## Ferramentas Utilizadas
- **Microcontrolador**: Raspberry Pi Pico W
- **Ambiente de Desenvolvimento**: VS Code
- **Simulador**: Wokwi
- **Linguagem**: C
- **SDK**: Pico SDK
- **Versionamento**: GitHub

---
## Atividade 1: Semáforo com Temporização
### Requisitos:
1. O semáforo inicia com o LED vermelho ligado, mudando para amarelo e depois verde.
2. O temporizador de alteração de estado é de 3 segundos.
3. A mudança de estado dos LEDs é implementada via callback da função `add_repeating_timer_ms()`.
4. O loop principal deve imprimir uma mensagem via porta serial a cada segundo (1000 ms).
5. O LED RGB é simulado no Wokwi utilizando GPIOs 11, 12 e 13.

---
## Atividade 2: Temporizador de Um Disparo (One Shot)
### Requisitos:
1. O usuário pressiona o botão (pushbutton), ligando todos os LEDs.
2. Os LEDs desligam sequencialmente a cada 3 segundos.
3. A mudança de estado é feita via callback da função `add_alarm_in_ms()`.
4. O botão só pode ser pressionado novamente após o último LED desligar.
5. O LED RGB é simulado no Wokwi utilizando GPIOs 11, 12 e 13.
6. Implementação opcional de debounce por software no botão.

---
## Como Executar o Projeto
1. Clone este repositório:
   ```sh
   git clone <git@github.com:VRjotta/atividades_aula_sincrona_29-01.git>
   ```
2. Configure o ambiente do Pico SDK no VS Code.
3. Abra o simulador Wokwi e carregue o código.
4. Compile e execute o código.

