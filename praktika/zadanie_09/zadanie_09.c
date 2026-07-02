/*
 * Задание 9 — кнопка PB2, LED PD3. 10 МГц. Atmel Studio.
 */

#ifndef F_CPU                   /* если частота ещё не задана */
#define F_CPU 10000000UL              /* частота кварца 10 МГц */
#endif                              /* конец блока F_CPU */

#include <avr/io.h>                   /* регистры DDRx, PORTx, PINx */
#include <util/delay.h>               /* функция _delay_ms */

int main(void)
{
    DDRB &= ~(1 << PB2);  /* PB2 — вход (кнопка) */
    PORTB |= (1 << PB2); /* подтяжка PB2 к +5 В */

    DDRD |= (1 << PD3);  /* PD3 — выход (светодиод) */
    PORTD &= ~(1 << PD3); /* LED погашен в начале */

    while (1) {                       /* бесконечный цикл */
        if (!(PINB & (1 << PB2))) { /* кнопка нажата */
            PORTD |= (1 << PD3);   /* зажечь LED */
        } else {                      /* кнопка отпущена */
            PORTD &= ~(1 << PD3);  /* погасить LED */
        }
        _delay_ms(10);                /* пауза 10 мс (антидребезг) */
    }
}