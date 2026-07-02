/*
 * Задание 12 — 7SEG PORTC, числа 8..36. 10 МГц. Atmel Studio.
 * Разряды PB0, PB1.
 */

#ifndef F_CPU                   /* если частота ещё не задана */
#define F_CPU 10000000UL              /* частота кварца 10 МГц */
#endif                              /* конец блока F_CPU */

#include <avr/io.h>                   /* регистры DDRx, PORTx, PINx */
#include <util/delay.h>               /* функция _delay_ms */

const unsigned char seg_table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void SSD_Show(unsigned char number)
{
    unsigned char tens;               /* цифра десятков */
    unsigned char ones;               /* цифра единиц */

    tens = number / 10;               /* вычислить десятки */
    ones = number % 10;               /* вычислить единицы */

    PORTC = seg_table[tens];   /* код десятков на сегменты PORTC */
    PORTB |= (1 << PB1); /* отключить разряд единиц PB1 */
    PORTB &= ~(1 << PB0); /* включить разряд десятков PB0 */
    _delay_ms(2);                     /* пауза мультиплексирования 2 мс */
    PORTB |= (1 << PB0); /* отключить разряд десятков */

    PORTC = seg_table[ones];   /* код единиц на сегменты PORTC */
    PORTB |= (1 << PB0); /* отключить разряд десятков */
    PORTB &= ~(1 << PB1); /* включить разряд единиц PB1 */
    _delay_ms(2);                     /* пауза мультиплексирования 2 мс */
    PORTB |= (1 << PB1); /* отключить разряд единиц */
}

int main(void)
{
    unsigned char value;              /* текущее число на индикаторе */

    value = 8;                    /* начальное значение */
    DDRC = 0xFF;               /* PORTC — все выходы (сегменты) */
    DDRB |= (1 << PB0) | (1 << PB1); /* выбор разрядов — выходы */
    PORTB |= (1 << PB0) | (1 << PB1); /* разряды выключены */

    while (1) {                       /* бесконечный цикл */
        SSD_Show(value);              /* показать число */
        _delay_ms(300);               /* пауза 300 мс перед сменой */
        value++;                      /* следующее число */
        if (value > 36) {          /* если вышли за предел */
            value = 8;              /* начать сначала */
        }
    }
}