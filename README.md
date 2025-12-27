# AVR UART Driver (Ring Buffer + Interrupts)

Легковесная библиотека для работы с UART на микроконтроллерах AVR (ATmega328p).
Реализует асинхронный прием данных через **Кольцевой Буфер (FIFO)** и прерывания, что предотвращает блокировку процессора.

## Особенности
- **Non-blocking Read:** Прием данных происходит в фоне (ISR).
- **Ring Buffer:** Эффективная очередь FIFO для входящих данных.
- **Bare Metal:** Написано на чистом C без Arduino Framework.
- **Modular:** Драйвер отделен от бизнес-логики (`uart.c`, `uart.h`).

## Инструменты
- **MCU:** ATmega328p (Arduino Nano)
- **F_CPU:** 16 MHz
- **Language:** C99
- **IDE:** VS Code + PlatformIO
