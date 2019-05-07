			.equ	left,	0
			.equ	data,	4
			.equ	right,	8
			.equ	NULL,	0

			.data
fmt1:		.asciz	"data(tree) = %4d, "
fmt2:		.asciz	"left = %4d, "
fmt3:		.asciz	"right = %4d\n"
fmt4:		.asciz	"left = NULL, "
fmt5:		.asciz	"right = NULL\n"

			.text
			.globl main

get_node:	stmfd sp!, {lr}
			mov r0, #8
			bl malloc
			mov r5, #0
			str r5, [r0]
			str r5, [r0, #8]
			ldmfd sp!, {lr}
			mov pc, lr



tree_ins:	push {fp, lr}
			add fp, sp, #4
			sub sp, sp, #12
			#Need Stack to keep origin value
			str r0, [fp, #-8]
			str r1, [fp, #-12]
			ldr r4, [fp, #-8]
			ldr r8, [fp, #-12]
			ldr r6, [r4]
			cmp r6, #0
			bne recurs
			bl get_node
			str r0, [r4]
			str r8, [r0, #4]
			b fin
recurs:		mov r0, r6
			ldr r2, [r0, #4]
			ldr r1, [fp, #-12]
			cmp r2, r1
			blt r_recurs
			bl tree_ins
			b fin
r_recurs:	add r0, r0, #8
			bl tree_ins
fin:		sub sp, fp, #4
			pop {fp, pc}
			#ldmfd sp!, {lr}
			#mov pc, lr



p_tree:		push {fp, lr}
			add fp, sp, #4
			sub sp, sp, #8
			mov r4, r0
			str r0, [fp, #-8]
			cmp r0, #0
			beq pfin
			ldr r0, =fmt1
			ldr r1, [r4, #4]
			bl printf
			ldr r6, [r4]
			cmp r6, #0
			beq not_left
			ldr r0, =fmt2
			ldr r1, [r6, #4]
			bl printf
r_chk:		ldr r6, [r4, #8]
			cmp r6, #0
			beq not_right
			ldr r0, =fmt3
			ldr r1, [r6, #4]
			bl printf
			b pfin
not_left:	ldr r0, =fmt4
			bl printf
			b r_chk
not_right:	ldr r0, =fmt5
			bl printf
pfin:		sub sp, fp, #4
			pop {fp, pc}



main:		push {fp, lr}
			add fp, sp, #4
			sub sp, sp, #8
			mov r3, #0
			str r3, [fp, #-8]
			mov r1, #10
			sub r0, fp, #8
			bl tree_ins
			mov r1, #20
			sub r0, fp, #8
			bl tree_ins
			mov r1, #5
			sub r0, fp, #8
			bl tree_ins
			sub r0, fp, #8
			ldr r0, [r0]
			bl p_tree
			mov r0, #0
			sub sp, fp, #4
			pop {fp, pc}
