/*
 * Copyright (C) 2001 MontaVista Software Inc.
 * Author: Jun Sun, jsun@mvista.com or jsun@junsun.net
 *
 * Copyright (C) 2015 Gan Quan <coin2028@hotmail.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */


#include <drivers/uart16550.h>

/* === CONFIG === */

#define         BASE                    0xffffffffbfe001e8
#define         MAX_BAUD                115200
#define		REG_OFFSET		1

/* === END OF CONFIG === */

/* register offset */
#define         OFS_RCV_BUFFER          (0*REG_OFFSET)
#define         OFS_TRANS_HOLD          (0*REG_OFFSET)
#define         OFS_SEND_BUFFER         (0*REG_OFFSET)
#define         OFS_INTR_ENABLE         (1*REG_OFFSET)
#define         OFS_INTR_ID             (2*REG_OFFSET)
#define         OFS_DATA_FORMAT         (3*REG_OFFSET)
#define         OFS_LINE_CONTROL        (3*REG_OFFSET)
#define         OFS_MODEM_CONTROL       (4*REG_OFFSET)
#define         OFS_RS232_OUTPUT        (4*REG_OFFSET)
#define         OFS_LINE_STATUS         (5*REG_OFFSET)
#define         OFS_MODEM_STATUS        (6*REG_OFFSET)
#define         OFS_RS232_INPUT         (6*REG_OFFSET)
#define         OFS_SCRATCH_PAD         (7*REG_OFFSET)

#define         OFS_DIVISOR_LSB         (0*REG_OFFSET)
#define         OFS_DIVISOR_MSB         (1*REG_OFFSET)

/* memory-mapped read/write of the port */
#define         UART16550_READ(y)    (*((volatile unsigned char *)(BASE + y)))
#define         UART16550_WRITE(y, z)  ((*((volatile unsigned char *)(BASE + y))) = z)

void
Uart16550Init(unsigned int baud, unsigned char data, unsigned char parity,
    unsigned char stop)
{
	/* disable interrupts */
	UART16550_WRITE(OFS_INTR_ENABLE, 0);

	/* set up buad rate */
	{ 
		uint32 divisor;

		/* set DIAB bit */
		UART16550_WRITE(OFS_LINE_CONTROL, 0x80);

		/* set divisor */
		divisor = MAX_BAUD / baud;
		UART16550_WRITE(OFS_DIVISOR_LSB, divisor & 0xff);
		UART16550_WRITE(OFS_DIVISOR_MSB, (divisor & 0xff00)>>8);

		/* clear DIAB bit */
		UART16550_WRITE(OFS_LINE_CONTROL, 0x0);
	}

	/* set data format */
	UART16550_WRITE(OFS_DATA_FORMAT, data | parity | stop);
}

unsigned char Uart16550GetPoll()
{
	while((UART16550_READ(OFS_LINE_STATUS) & 0x1) == 0);
	return UART16550_READ(OFS_RCV_BUFFER);
}


void Uart16550Put(unsigned char byte)
{
	while ((UART16550_READ(OFS_LINE_STATUS) &0x20) == 0);
	UART16550_WRITE(OFS_SEND_BUFFER, byte);
}
