/*
 * Copyright (C) 2015 Gan Quan <coin2028@hotmail.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#include <asm/syscalldefs.h>
#include <asm/ptrace.h>
#include <asm/trap.h>
#include <asm/cpu.h>
#include <printk.h>
#include <panic.h>

void forkret(struct trapframe *tf)
{
	printk("Entering forkret with trapframe %016x\r\n", tf);
	printk("kernelsp[0] = %016x\r\n", kernelsp[0]);
	dump_trapframe(tf);
	arch_forkret(tf);
	panic("Returned from arch_forkret???\r\n");
}
