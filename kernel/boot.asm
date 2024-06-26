M_ALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ M_ALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384 ; 16 KiB
stack_top:

section .text

global _start
[extern kernel_main]
_start:
    mov esp, stack_top

    call kernel_main

    cli
    hlt
    jmp $
