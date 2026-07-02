/*
 * Задание 15 — кнопка PC6, LED PB5. 8 МГц. Atmel Studio.
 */

#ifndef F_CPU                   /* если частота ещё не задана */
#define F_CPU 8000000UL              /* частота кварца 8 МГц */
#endif                              /* конец блока F_CPU */

#include <avr/io.h>                   /* регистры DDRx, PORTx, PINx */
#include <util/delay.h>               /* функция _delay_ms */

int main(void)
{
    DDRC &= ~(1 << PC6);  /* PC6 — вход (кнопка) */
    PORTC |= (1 << PC6); /* подтяжка PC6 к +5 В */

    DDRB |= (1 << PB5);  /* PB5 — выход (светодиод) */
    PORTB &= ~(1 << PB5); /* LED погашен в начале */

    while (1) {                       /* бесконечный цикл */
        if (!(PINC & (1 << PC6))) { /* кнопка нажата */
            PORTB |= (1 << PB5);   /* зажечь LED */
        } else {                      /* кнопка отпущена */
            PORTB &= ~(1 << PB5);  /* погасить LED */
        }
        _delay_ms(10);                /* пауза 10 мс (антидребезг) */
    }
}