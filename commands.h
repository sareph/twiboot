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

/* SLA+R */
#define CMD_READ_MODE		0x00
#define CMD_READ_VERSION	0x01
#define CMD_READ_MEMORY		0x02
#define CMD_WAIT			0x03
/* internal mappings */
#define CMD_READ_CHIPINFO	(0x10 | CMD_READ_MEMORY)
#define CMD_READ_FLASH		(0x20 | CMD_READ_MEMORY)
#define CMD_READ_EEPROM		(0x30 | CMD_READ_MEMORY)
#define CMD_READ_PARAMETERS	(0x40 | CMD_READ_MEMORY)	/* only in APP */

#define MODE_BOOTLOADER 	0x55
#define MODE_APPLICATION 	0xAA

/* SLA+W */
#define CMD_SWITCH_APPLICATION	CMD_READ_VERSION
#define CMD_WRITE_MEMORY	CMD_READ_MEMORY
/* internal mappings */
#define CMD_BOOT_BOOTLOADER	(0x10 | CMD_SWITCH_APPLICATION)	/* only in APP */
#define CMD_BOOT_APPLICATION	(0x20 | CMD_SWITCH_APPLICATION)
#define CMD_WRITE_CHIPINFO	(0x10 | CMD_WRITE_MEMORY)	/* invalid */
#define CMD_WRITE_FLASH		(0x20 | CMD_WRITE_MEMORY)
#define CMD_WRITE_EEPROM	(0x30 | CMD_WRITE_MEMORY)
#define CMD_WRITE_PARAMETERS	(0x40 | CMD_WRITE_MEMORY)	/* only in APP */

/* CMD_SWITCH_APPLICATION parameter */
#define BOOTTYPE_BOOTLOADER	0x00				/* only in APP */
#define BOOTTYPE_APPLICATION	0x80

/* CMD_{READ|WRITE}_* parameter */
#define MEMTYPE_CHIPINFO	0x00
#define MEMTYPE_FLASH		0x01
#define MEMTYPE_EEPROM		0x02
#define MEMTYPE_PARAMETERS	0x03				/* only in APP */
