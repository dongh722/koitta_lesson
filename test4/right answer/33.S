/* 수업중에 활용했던 아래 코드 참고 */

	.text
	.arm

	.global _gio_a5_on_
    .asmfunc

_gio_a5_on_
	;push {r11, lr}
	ldr r4, gio_a
	ldr r5, gio_a_5dir
	mov r6, #0x20
	str r5, [r4]
	str r6, [r4, #8]
	bx lr
	;pop {r11, pc}
	;mov r4, #0xFFF7BC34

gio_a		.word	0FFF7BC34h
gio_a_5dir	.word	0FFFFFFFFh
gio_a_5out	.word	000000020h
