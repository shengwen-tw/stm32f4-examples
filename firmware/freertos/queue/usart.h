#ifndef USART_H
#define USART_H

void usart3_init(int baudrate);

void usart3_putc(char data);
void usart3_puts(char *string);

#endif
