		.data
fmt:	.asciz	"test.txt"

		.text
		.globl main

main:
		push {fp, lr}
		add fp, sp, #4
		sub sp, sp, #272
		mov r3, #0
		str r3, [fp, #-264]
		sub r3, fp, #260
		mov r2, #252
		mov r1, #0
		mov r0, r3
		bl memset
		mov r1, #0
		ldr r0, =fmt
		bl open
		str r0, [fp, #-272]
		b init
mwrite:
		ldr r2, [fp, #-268]
		sub r3, fp, #264
		mov r1, r3
		mov r0, #0
		bl write
init:
		sub r3, fp, #264
		mov r2, #256
		mov r1, r3
		ldr r0, [fp, #-272]
		bl read
		str r0, [fp, #-268]
		ldr r3, [fp, #-268]
		cmp r3, #0
		bne mwrite
		ldr r0, [fp, #-272]
		bl close
		mov r0, #0
		sub sp, fp, #4
		pop {fp, pc}
