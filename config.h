/***************************************************************************
 *   Copyright (C) 08/2010 by Olaf Rempel                                  *
 *   razzor@kopf-tisch.de                                                  *
 *   Copyright (C) 2016 Tomek Nagisa, Kaworu                               *
 *   kaworu@k2t.eu                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License,               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

/*
 * atmega8:
 * Fuse H: 0xda (512 words bootloader)
 * Fuse L: 0x84 (8Mhz internal RC-Osz., 2.7V BOD)
 *
 * atmega88:
 * Fuse E: 0xfa (512 words bootloader)
 * Fuse H: 0xdd (2.7V BOD)
 * Fuse L: 0xc2 (8Mhz internal RC-Osz.)
 *
 * atmega168:
 * Fuse E: 0xfa (512 words bootloader)
 * Fuse H: 0xdd (2.7V BOD)
 * Fuse L: 0xc2 (8Mhz internal RC-Osz.)
 *
 * atmega328p:
 * Fuse E: 0xfd (2.7V BOD)
 * Fuse H: 0xdc (512 words bootloader)
 * Fuse L: 0xc2 (8Mhz internal RC-Osz.)
 */

#if defined (__AVR_ATmega8__)
#define VERSION_STRING		"TWIBOOT m8v2.2"
#define SIGNATURE_BYTES		0x1E, 0x93, 0x07

#elif defined (__AVR_ATmega88__)
#define VERSION_STRING		"TWIBOOT m88v2.2"
#define SIGNATURE_BYTES		0x1E, 0x93, 0x0A

#elif defined (__AVR_ATmega168__)
#define VERSION_STRING		"TWIBOOT m168v2.2"
#define SIGNATURE_BYTES		0x1E, 0x94, 0x06

#elif defined (__AVR_ATmega328P__)
#define VERSION_STRING		"TWIBOOTm328pv2.2"
#define SIGNATURE_BYTES		0x1E, 0x95, 0x0F

#else
#error MCU not supported
#endif

#define EEPROM_SUPPORT	1
#define LED_SUPPORT		0
#define AUTO_EXIT		0

/* 25ms @8MHz */
#define TIMER_RELOAD	(0xFF - 195)

/* 40 * 25ms */
#define TIMEOUT			40

#if LED_SUPPORT
#define LED_INIT()		DDRB = ((1<<PORTB4) | (1<<PORTB5))
#define LED_RT_ON()		PORTB |= (1<<PORTB4)
#define LED_RT_OFF()	PORTB &= ~(1<<PORTB4)
#define LED_GN_ON()		PORTB |= (1<<PORTB5)
#define LED_GN_OFF()	PORTB &= ~(1<<PORTB5)
#define LED_GN_TOGGLE()	PORTB ^= (1<<PORTB5)
#define LED_OFF()		PORTB = 0x00
#else
#define LED_INIT()
#define LED_RT_ON()
#define LED_RT_OFF()
#define LED_GN_ON()
#define LED_GN_OFF()
#define LED_GN_TOGGLE()
#define LED_OFF()
#endif

#ifndef TWI_ADDRESS
#define TWI_ADDRESS		0x7C
#endif
