// put "_start" in the section called text.boot & we put that section first in memory (ld)"
.section .text.boot
/*extern the start label (for the linker)*/
.global _start

_start:
    // setup sp
    ldr     x1, =0x80000
    mov     sp, x1
    
    bl main


/* label to return to when return 0 */
/* wfe = wait for event */
_return:
    wfe 
    b _return  
