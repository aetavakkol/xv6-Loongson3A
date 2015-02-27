/*
 * Copyright (C) 2015 Gan Quan <coin2028@hotmail.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#ifndef _MM_VMM_H
#define _MM_VMM_H

#include <config.h>

#ifdef CONFIG_HPT
#include <asm/mm/hier/vmm.h>
#endif

#ifdef CONFIG_IPT
#include <asm/mm/inv/vmm.h>
#endif

/*
 * Page table implementation function prototypes.
 */

/*
 * Bootstrap a page table.
 */
void pgtable_bootstrap(void);
/*
 * Get a page table descriptor for virtual address @vaddr inside the page
 * table @pgtable, creating necessary intermediate objects if allowed (by
 * setting @create), storing the result descriptor in @result.
 *
 * NOTE: The page table and result are depicted as void pointers for
 *       allowing different page table implementations.
 */
int pgtable_get(void *pgtable, ptr_t vaddr, bool create, void *result);
/*
 * Insert (and possibly replace if @replace is set) a page @page into
 * page table @pgtable with virtual address @vaddr.  If a replacement
 * occur, the old page will be stored at @replaced_page.
 */
int pgtable_insert(void *pgtable, ptr_t vaddr, struct page *page,
    unsigned int perm, bool replace, struct page **replaced_page);
/* Remove a virtual address. */
struct page *pgtable_remove(void *pgtable, ptr_t vaddr);

void test_pgtable(void);
void test_tlb(void);

#endif