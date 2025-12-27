#include "uart.h"

// --- Приватные переменные (Кольцевой буфер) ---

static volatile char rx_buffer[UART_BUFFER_SIZE];
static volatile uint8_t rx_head = 0; // Индекс, куда пишет ISR (Прерывание)
static volatile uint8_t rx_tail = 0; // Индекс, откуда читает Main (Программа)

// --- Инициализация ---
void UART_Init(uint16_t baut){
    // Расчет делителя частоты для заданной скорости (Datasheet)
    uint16_t ubrr = (F_CPU/16/baut) -1;

    // Записываем скорость в регистры UBRR (старший и младший байт)
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)(ubrr);

    // Включаем модули:
    // RXEN0 - Приемник
    // TXEN0 - Передатчик
    // RXCIE0 - Прерывание при завершении приема (Interrupt Enable)
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

    // Формат кадра: 8 бит данных, 1 стоп-бит
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// --- Проверка наличия данных ---
uint8_t UART_Available(void){
    return (UART_BUFFER_SIZE + rx_head - rx_tail) % UART_BUFFER_SIZE;
}

// --- Чтение данных (извлекаем из очереди) ---
char UART_Read(void){
    if (rx_head == rx_tail) return 0;

    char data = rx_buffer[rx_tail];

    rx_tail = (rx_tail + 1) % UART_BUFFER_SIZE;

    return data;
}

// --- Отправка байта ---
void UART_Write(char data){
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

// --- Отправка строки ---
void UART_Print(char* str){
    while (*str) UART_Write(*str++);
}

// --- ОБРАБОТЧИК ПРЕРЫВАНИЯ (ISR) ---
// Вызывается автоматически, когда приходит байт по UART.
// Работает "в фоне", прерывая main().
ISR(USART_RX_vect) {
    
    // 1. Забираем байт из регистра железа
    char data = UDR0;

    // 2. Вычисляем позицию для следующего байта
    uint8_t next_head = (rx_head + 1) % UART_BUFFER_SIZE;

    // 3. Проверка на переполнение:
    // Если следующая позиция головы совпадает с хвостом, значит буфер полон.
    // В этом случае мы просто игнорируем новый байт (можно добавить счетчик ошибок).
    if (next_head != rx_tail) {
        rx_buffer[rx_head] = data; // Сохраняем
        rx_head = next_head;       // Сдвигаем голову
    }
}