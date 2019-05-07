			.data
fmt1:		.asciz	"dx = %.10f\n"
fmt2:		.asciz	"dy = %.10f\n"
fmt3:		.asciz	"int_nelem = %d\n"
fmt4:		.asciz	"sum = %f\n"
fmt5:		.asciz	"res = %f\n"
delta:		.word	953267991

			.text
			.globl main

calc_piece:
			str fp, [sp, #-4]!
			add fp, sp, #0
			sub sp, sp, #12
			str r0, [fp, #-8]
			str r1, [fp, #-12]
			vldr.32	s13, [fp, #-8]
			vldr.32	s14, [fp, #-12]
			vdiv.f32 s15, s13, s14
			vcvt.s32.f32 s15, s15
			vmov r3, s15
			mov r0, r3
			sub sp, fp, #0
			ldr fp, [sp], #4
			bx lr

calc_int_3x_2_7x:
			push {fp, lr}
			add fp, sp, #4
			sub sp, sp, #40
			str r0, [fp, #-40]
			str r1, [fp, #-44]
			mov r3, #0
			str r3, [fp, #-32]
			mov r3, #0
			str r3, [fp, #-28]
			mov r3, #1073741824
			str r3, [fp, #-24]
			ldr r3, =delta
			ldr r3, [r3]
			str r3, [fp, #-20]
			vldr.32	s15, [fp, #-20]
			vcvt.f64.f32 d16, s15
			vldr.32	s15, [fp, #-24]
			vcvt.f64.f32 d17, s15
			vmov r2, r3, d17
			vmov r0, r1, d16
			bl pow
			vmov d16, r0, r1
			vcvt.f32.f64 s15, d16
			vstr.32	s15, [fp, #-16]
			vldr.32	s15, [fp, #-20]
			vcvt.f64.f32 d16, s15
			vmov r2, r3, d16
			ldr r0, =fmt1
			bl printf
			vldr.32	s15, [fp, #-16]
			vcvt.f64.f32 d16, s15
			vmov r2, r3, d16
			ldr r0, =fmt2
			bl printf
			mov r3, #0
			str r3, [fp, #-12]
			vldr.32	s14, [fp, #-44]
			vldr.32	s15, [fp, #-40]
			vsub.f32 s15, s14, s15
			ldr r1, [fp, #-20]
			vmov r0, s15
			bl calc_piece
			str r0, [fp, #-8]
			ldr r1, [fp, #-8]
			ldr r0, =fmt3
			bl printf
			ldr r3, [fp, #-12]
			str r3, [fp, #-36]
			b loop_init
loop:
			vldr.32	s14, [fp, #-28]
			vldr.32	s15, [fp, #-20]
			vadd.f32 s15, s14, s15
			vstr.32	s15, [fp, #-28]
			vldr.32	s14, [fp, #-28]
			vldr.32	s15, [fp, #-40]
			vadd.f32 s15, s14, s15
			vcvt.f64.f32 d16, s15
			vldr.32	s15, [fp, #-24]
			vcvt.f64.f32 d17, s15
			vmov r2, r3, d17
			vmov r0, r1, d16
			bl pow
			vmov d17, r0, r1
			vmov.f64 d16, #3.0e+0
			vmul.f64 d17, d17, d16
			vldr.32	s14, [fp, #-28]
			vldr.32	s15, [fp, #-40]
			vadd.f32 s15, s14, s15
			vmov.f32 s14, #7.0e+0
			vmul.f32 s15, s15, s14
			vcvt.f64.f32 d16, s15
			vadd.f64 d16, d17, d16
			vcvt.f32.f64 s15, d16
			vstr.32	s15, [fp, #-16]
			vldr.32	s14, [fp, #-20]
			vldr.32	s15, [fp, #-16]
			vmul.f32 s15, s14, s15
			vldr.32	s14, [fp, #-32]
			vadd.f32 s15, s14, s15
			vstr.32	s15, [fp, #-32]
			ldr r3, [fp, #-36]
			add r3, r3, #1
			str r3, [fp, #-36]
loop_init:
			ldr r2, [fp, #-36]
			ldr r3, [fp, #-8]
			cmp r2, r3
			blt loop
			vldr.32	s15, [fp, #-32]
			vcvt.f64.f32 d16, s15
			vmov r2, r3, d16
			ldr r0, =fmt4
			bl printf
			ldr r3, [fp, #-32]
			mov r0, r3
			sub sp, fp, #4
			pop {fp, pc}

main:
			push {fp, lr}
			add fp, sp, #4
			sub sp, sp, #8
			mov r1, #1073741824
			mov r0, #1065353216
			bl calc_int_3x_2_7x
			str r0, [fp, #-8]
			vldr.32	s15, [fp, #-8]
			vcvt.f64.f32	d16, s15
			vmov r2, r3, d16
			ldr r0, =fmt5
			bl printf
			mov r0, #0
			sub sp, fp, #4
			pop {fp, pc}
