		.data
fmt:	.asciz	"Let's go pof asm"

		.text
		.globl main

test:
		push {fp, lr}
		ldr r0, =fmt
		bl puts
		pop {fp, pc}

main:	push {fp, lr}
		ldr r0, =test
		blx r0
		mov r0, #0
		pop {fp, pc}
