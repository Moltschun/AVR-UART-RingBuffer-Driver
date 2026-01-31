# AVR UART Driver (Ring Buffer + Interrupts)

![AVR](https://img.shields.io/badge/AVR-sucsses?style=for-the-badge&logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=black)
![Bare Metal](https://img.shields.io/badge/Bare_Metal-red?style=for-the-badge)
![Peripherals](https://img.shields.io/badge/UART-darkgreen?style=for-the-badge)

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


