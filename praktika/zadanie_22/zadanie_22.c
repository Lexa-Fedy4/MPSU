/*
 * Задание 22 — кнопка PB6, LED PC5. 8 МГц. Atmel Studio.
 */

#ifndef F_CPU                   /* если частота ещё не задана */
#define F_CPU 8000000UL              /* частота кварца 8 МГц */
#endif                              /* конец блока F_CPU */

#include <avr/io.h>                   /* регистры DDRx, PORTx, PINx */
#include <util/delay.h>               /* функция _delay_ms */

int main(void)
{
    DDRB &= ~(1 << PB6);  /* PB6 — вход (кнопка) */
    PORTB |= (1 << PB6); /* подтяжка PB6 к +5 В */

    DDRC |= (1 << PC5);  /* PC5 — выход (светодиод) */
    PORTC &= ~(1 << PC5); /* LED погашен в начале */

    while (1) {                       /* бесконечный цикл */
        if (!(PINB & (1 << PB6))) { /* кнопка нажата */
            PORTC |= (1 << PC5);   /* зажечь LED */
        } else {                      /* кнопка отпущена */
            PORTC &= ~(1 << PC5);  /* погасить LED */
        }
        _delay_ms(10);                /* пауза 10 мс (антидребезг) */
    }
}