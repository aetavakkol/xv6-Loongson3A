/*
 * Copyright (C) 2015 Gan Quan <coin2028@hotmail.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */

#include <asm/ld.h>
#include <asm/bootinfo.h>
#include <asm/mipsregs.h>
#include <asm/addrspace.h>
#include <asm/mm/page.h>
#include <asm/memrw.h>
#include <mm/mmap.h>
#include <mm/vmm.h>
#include <mm/slab.h>
#include <ds/list.h>
#include <printk.h>
#include <string.h>

unsigned long highmem_base_pfn;

unsigned long base_pfn;

/*
 * An array of page structures tracking information of (high memory) physical
 * pages.
 * NOTE: This array locates in high memory.
 */
struct page *page_array;

struct free_page_set free_page_set;

static void init_free_page_list(size_t nr_pages, size_t nr_occupied)
{
	size_t i;

	list_init(free_page_list);

	for (i = nr_occupied; i < nr_pages; ++i) {
		list_add_before(free_page_list, &(page_array[i].list_node));
	}

	nr_free_pages = nr_pages - nr_occupied;
	
	printk("Built free page list of %d pages\r\n", nr_free_pages);
}

void init_page_array(size_t nr_pages)
{
	unsigned long page_array_bytes = nr_pages * sizeof(struct page);
	unsigned long page_array_pages = NR_PAGES_NEEDED(page_array_bytes);

	printk("PAGEARRAY: %016x\r\n", page_array);
	memset(page_array, 0, page_array_bytes);
	/*
	 * Since the page array itself is inside high memory, we need to
	 * count and reserve the first not-so-few pages the page array
	 * occupies.
	 *
	 * These pages will *NEVER* be inserted into free page list.
	 */
	unsigned long i;

	for (i = 0; i < nr_pages; ++i) {
		list_init(&(page_array[i].list_node));
	}
	printk("%d pages initialized.\r\n", nr_pages);

	for (i = 0; i < page_array_pages; ++i) {
		reserve_page(&(page_array[i]));
		page_array[i].type = PGTYPE_PGSTRUCT;
	}

	printk("%d pages reserved for page structures.\r\n", page_array_pages);

	init_free_page_list(nr_pages, page_array_pages);
}

void mm_init(void)
{
	printk("Size of page struct: %d\r\n", sizeof(struct page));
	arch_mm_init();
	slab_bootstrap();
	printk("Current free pages: %d\r\n", nr_free_pages);

	mm_test();
}
