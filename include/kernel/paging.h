#ifndef _PAGING_H
#define _PAGING_H

#include <stddef.h>
#include <kernel/isr.h>

typedef struct page
{
   size_t present    : 1;   // Page present in memory
   size_t rw         : 1;   // Read-only if clear, readwrite if set
   size_t user       : 1;   // Supervisor level only if clear
   size_t accessed   : 1;   // Has the page been accessed since last refresh?
   size_t dirty      : 1;   // Has the page been written to since last refresh?
   size_t unused     : 7;   // Amalgamation of unused and reserved bits
   size_t frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
   page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
   /**
      Array of pointers to pagetables.
   **/
   page_table_t *tables[1024];
   /**
      Array of pointers to the pagetables above, but gives their *physical*
      location, for loading into the CR3 register.
   **/
   size_t tables_physical[1024];
   /**
      The physical address of tablesPhysical. This comes into play
      when we get our kernel heap allocated and the directory
      may be in a different location in virtual memory.
   **/
   size_t physical_addr;
} page_directory_t;

/**
  Sets up the environment, page directories etc and
  enables paging.
**/
void initialise_paging();

/**
  Causes the specified page directory to be loaded into the
  CR3 register.
**/
void switch_page_directory(page_directory_t *new);

/**
  Retrieves a pointer to the page required.
  If make == 1, if the page-table in which this page should
  reside isn't created, create it!
**/
page_t *get_page(size_t address, size_t make, page_directory_t *dir);

/**
  Handler for page faults.
**/
void page_fault(registers_t regs); 

#endif
