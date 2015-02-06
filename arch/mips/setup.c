/*
 * Copyright (C) 1995 Linus Torvalds
 * Copyright (C) 1995 Waldorf Electronics
 * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 01, 02, 03  Ralf Baechle
 * Copyright (C) 1996 Stoned Elipot
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Copyright (C) 2000, 2001, 2002, 2007  Maciej W. Rozycki
 * Copyright (C) 2015 Gan Quan <coin2028@hotmail.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#include <asm/bootinfo.h>
#include <asm/cpu.h>
#include <printk.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
 * fw_arg0 and fw_arg1 serves as argc and argv for kernel.
 *
 * fw_arg2 stores a pointer to environment strings.
 *
 * fw_arg3 is likely reserved(?)
 */
unsigned long fw_arg0, fw_arg1, fw_arg2, fw_arg3;

unsigned long memsize, highmemsize, cpu_clock_freq, bus_clock_freq;

static inline void
parse_ulong_option(const char *envs, const char *option, unsigned long *var)
{
	int len_option = strlen(option);
	if ((strncmp(envs, option, len_option) == 0) &&
	    (envs[len_option] == '=')) {
		*var = strtoul(&envs[len_option + 1], NULL, 10);
	}
}

void
parse_env(void)
{
	signed int *envp = (signed int *)fw_arg2;
	char *envs = (char *)(unsigned long)(*envp);
	for ( ; *envs != '\0'; ) {
		parse_ulong_option(envs, "memsize", &memsize);
		envs += strlen(envs) + 1;
	}
	printk("Memory size = %u\r\n", memsize);
}

void
setup_arch(void)
{
	cpu_probe();
	parse_env();
	return;
}
