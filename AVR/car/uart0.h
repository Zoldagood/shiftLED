#ifndef	__UART_H__
#define	__UART_H__

#define	LENGTH_RX0_BUFFER	20
#define	LENGTH_TX0_BUFFER	20

#define BR9600		103
#define BR57600		16
#define BR115200	8

extern	void UART0_init(unsigned int ubrr_baud);
extern  void UART0_print_string(char *str);
extern	void UART0_transmit(char data);
extern	int UART0_receive(FILE *stream);
extern	int	UART0_rx_check(void);

#endif
