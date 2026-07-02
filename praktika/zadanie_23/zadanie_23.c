/*
 * Задание 23 — 7SEG PORTD, числа 0..10. 10 МГц. Atmel Studio.
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

    PORTD = seg_table[tens];   /* код десятков на сегменты PORTD */
    PORTC |= (1 << PC1); /* отключить разряд единиц PC1 */
    PORTC &= ~(1 << PC0); /* включить разряд десятков PC0 */
    _delay_ms(2);                     /* пауза мультиплексирования 2 мс */
    PORTC |= (1 << PC0); /* отключить разряд десятков */

    PORTD = seg_table[ones];   /* код единиц на сегменты PORTD */
    PORTC |= (1 << PC0); /* отключить разряд десятков */
    PORTC &= ~(1 << PC1); /* включить разряд единиц PC1 */
    _delay_ms(2);                     /* пауза мультиплексирования 2 мс */
    PORTC |= (1 << PC1); /* отключить разряд единиц */
}

int main(void)
{
    unsigned char value;              /* текущее число на индикаторе */

    value = 0;                    /* начальное значение */
    DDRD = 0xFF;               /* PORTD — все выходы (сегменты) */
    DDRC |= (1 << PC0) | (1 << PC1); /* выбор разрядов — выходы */
    PORTC |= (1 << PC0) | (1 << PC1); /* разряды выключены */

    while (1) {                       /* бесконечный цикл */
        SSD_Show(value);              /* показать число */
        _delay_ms(300);               /* пауза 300 мс перед сменой */
        value++;                      /* следующее число */
        if (value > 10) {          /* если вышли за предел */
            value = 0;              /* начать сначала */
        }
    }
}