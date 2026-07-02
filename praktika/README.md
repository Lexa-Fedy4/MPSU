# Практические задания

Каждое задание — в отдельной папке:

```
zadanie_01/
  zadanie_01.c       — код (microC)
  proteus_shema.md   — схема для Proteus 8
...
zadanie_30/
```

Общие правила сборки: [PROTEUS_OBSCHEE.md](PROTEUS_OBSCHEE.md)

## microC PRO for PIC (задание 1)

МК PIC16F84A, частота 8 МГц. Стиль масок как в Atmel Studio: `(1 << PBx)`.

## Atmel Studio / avr-gcc (задания 2–30)

МК ATmega328P. Подключите `<avr/io.h>`, `<util/delay.h>`, задайте `F_CPU`, используйте `_delay_ms()`.
