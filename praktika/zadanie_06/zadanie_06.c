/*
 * Задание 6 — кнопка PB1, LED PC3. 10 МГц. Atmel Studio.
 */

#ifndef F_CPU                   /* если частота ещё не задана */
#define F_CPU 10000000UL              /* частота кварца 10 МГц */
#endif                              /* конец блока F_CPU */

#include <avr/io.h>                   /* регистры DDRx, PORTx, PINx */
#include <util/delay.h>               /* функция _delay_ms */

int main(void)
{
    DDRB &= ~(1 << PB1);              /* PB1 — вход (кнопка) */
    PORTB |= (1 << PB1);              /* подтяжка PB1 к +5 В */

    DDRC |= (1 << PC3);               /* PC3 — выход (светодиод) */
    PORTC &= ~(1 << PC3);             /* LED погашен в начале */

    while (1) {                       /* бесконечный цикл */
        if (!(PINB & (1 << PB1))) {   /* кнопка нажата (лог. 0 на PB1) */
            PORTC |= (1 << PC3);      /* зажечь LED */
        } else {                      /* кнопка отпущена */
            PORTC &= ~(1 << PC3);     /* погасить LED */
        }
        _delay_ms(10);                /* пауза 10 мс (антидребезг) */
    }
}
