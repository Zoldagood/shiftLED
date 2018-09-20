/*
 * uart1.h
 *
 * Created: 2018-09-12 오전 11:29:05
 *  Author: kccistc
 */ 

#ifndef UART1_H_
#define UART1_H_

#define	LENGTH_RX1_BUFFER	20
#define	LENGTH_TX1_BUFFER	20

#define BR9600		103
#define BR57600		16
#define BR115200	8

extern	void UART1_init(unsigned int ubrr_baud);
extern	int UART1_receive();
extern	int	UART1_rx_check(void);
extern	void UART1_transmit(char data);
extern	void UART1_print_string(char *str);

#endif /* UART1_H_ */