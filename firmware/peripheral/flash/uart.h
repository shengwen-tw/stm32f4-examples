#ifndef __UART_H__
#define __UART_H__

void usart3_init(void);
char usart_getc(void);
void usart_putc(char data);
void usart_puts(char *string);

#endif
