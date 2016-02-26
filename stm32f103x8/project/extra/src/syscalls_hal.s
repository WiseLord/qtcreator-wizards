.syntax unified
.cpu cortex-m3
.fpu softvfp
.thumb

.section	.text._sbrk_getHeapStartAddress
.weak		_sbrk_getHeapStartAddress
.type		_sbrk_getHeapStartAddress, %function

_sbrk_getHeapStartAddress:
    ldr r0, = __HeapStart
    bx lr
