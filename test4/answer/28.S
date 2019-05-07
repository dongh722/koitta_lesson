		.data
fmt:	.asciz	"data = %d, "
fmt1:	.asciz	"left = %4d, "
fmt2:	.asciz	"left = NULL, "
fmt3:	.asciz	"right = %4d\n\n"
fmt4:	.asciz	"right = NULL\n\n"

get_node:	push {r1,r2,r3,lr}
			mov	r0, #12
			bl	malloc
			mov r1,	#0
			str	r1,	[r0,#4]
			str	r1,	[r0,#8]
			pop {r1,r2,r3,lr}

tree_ins:	push {r11,lr}
			add r11, sp, #4
			sub	sp, sp, #4

			str r0, [r11,#-8]
			ldr	r2, [r0]
			mov	r3, r0

tree_loop:	cmp r2, #0
			bgt	print_fin

			bl get_node
			str r0, [r3]
			str r1, [r0]
			b ins_fin

link_lmov:	ldr r2, [r0]
			cmp r2, r1
			blt	link_rmov
			ldr r2, [r0,#4]
			add r3, r0, #4
			b	tree_loop

link_rmov:	ldr r2, [r0,#8]
			add r3, r0, #8
			b	tree_loop

ins_fin:	sub sp, r11, #4
			pop	{r11,pc}


print_now:	push {r11,lr}
			add r11, sp, #4
			sub sp, sp, #4
			cmp r1, #0
			beq	print_now_fin
			str r1, [r11, #-8]
			ldr r0, =fmt
			ldr r1, [r1]
			bl printf
			
print_left:	ldr r2,[r11,#-8]
			ldr r2, [r2,#4]
			cmp r2, #0
			beq print_lnull
			ldr r0, =fmt1
			ldr r1, [r2]
			bl printf
			
print_right:ldr r2, [r11,#-8]
			ldr r2, [r2, #8]
			cmp r2, #0
			beq print_rnull
			ldr r0, =fmt3
			ldr r1, [r2]
			bl printf
			b print_now_fin

print_lnull: ldr r0, =fmt2
			 bl printf
			b print_right
print_rnull: ldr r0, =fmt4
			 bl printf

print_now_fin:	sub sp, r11, #4
				pop {r11,pc}

print_tree: push {r11,lr}
			add r11, sp, #4
			sub sp, sp, #4
			str r0, [r11,#-8]
			mov r1, r0
			bl print_now
			ldr r0, [r11,#-8]
			ldr r0, [r0,#4]
			bl print_tree
			ldr r0, [r0,#8]
			bl print_tree
			sub sp, r11, #4
			pop {r11,pc}

main:	push {r11, lr}
		add r11, sp, #48
		sub sp, sp, #4
		mov r0, #0
		str r0, [r11, #-52]
		str r0,	[r11, #-48]
		mov r0, #50
		str r0, [r11, #-44]
		mov r0, #100
		str r0, [r11, #-40]
		mov r0, #25
		str r0, [r11, #-36]
		mov r0, #17
		str r0, [r11, #-32]
		mov r0, #23
		str r0, [r11, #-28]
		mov r0, #15
		str r0, [r11, #-24]
		mov	r0, #20
		str r0, [r11, #-20]
		mov r0, #75
		str r0, [r11, #-16]
		mov r0, #80
		str r0, [r11, #-12]
		mov r0, #0
		str r0, [r11, #-8]
		sub r3, r11, #44
main_loop:	
			ldr r2, [r3]
			cmp r2, #0
			addeq r3
			

			
