			.data
fmt:		.asciz	"real = %f, imag = %f\n"
c_data1:	.word	1073741824
			.word	1073741824
c_data2:	.word	1065353216
			.word	1073741824

			.text
			.globl main

complex_mult:
			str fp, [sp, #-4]!
			add fp, sp, #0
			sub sp, sp, #20
			sub ip, fp, #12
			stm ip, {r0, r1}
			sub r1, fp, #20
			stm r1, {r2, r3}
			vldr.32	s14, [fp, #-12]
			vldr.32	s15, [fp, #-20]
			vmul.f32 s14, s14, s15
			vldr.32	s13, [fp, #-8]
			vldr.32	s15, [fp, #-16]
			vmul.f32 s15, s13, s15
			vsub.f32 s15, s14, s15
			ldr r3, [fp, #4]
			vstr.32	s15, [r3]
			vldr.32	s14, [fp, #-12]
			vldr.32	s15, [fp, #-16]
			vmul.f32 s14, s14, s15
			vldr.32	s13, [fp, #-8]
			vldr.32	s15, [fp, #-20]
			vmul.f32 s15, s13, s15
			vadd.f32 s15, s14, s15
			ldr r3, [fp, #4]
			vstr.32	s15, [r3, #4]
			nop
			sub sp, fp, #0
			ldr fp, [sp], #4
			bx lr

print_complex:
			push {fp, lr}
			add fp, sp, #4
			sub sp, sp, #16
			sub r3, fp, #12
			stm r3, {r0, r1}
			vldr.32	s15, [fp, #-12]
			vcvt.f64.f32 d17, s15
			vldr.32	s15, [fp, #-8]
			vcvt.f64.f32 d16, s15
			vstr.64	d16, [sp]
			vmov r2, r3, d17
			ldr r0, =fmt
			bl printf
			nop
			sub sp, fp, #4
			pop {fp, pc}

main:
			push {fp, lr}
			add fp, sp, #4
			sub sp, sp, #40
			ldr r2, =c_data1
			sub r3, fp, #32
			ldm r2, {r0, r1}
			stm r3, {r0, r1}
			ldr r2, =c_data2
			sub r3, fp, #24
			ldm r2, {r0, r1}
			stm r3, {r0, r1}
			sub r3, fp, #16
			str r3, [sp]
			sub r3, fp, #24
			ldm r3, {r2, r3}
			sub r1, fp, #32
			ldm r1, {r0, r1}
			bl complex_mult
			sub r3, fp, #16
			ldm r3, {r0, r1}
			bl print_complex
			mov r0, #0
			sub sp, fp, #4
			pop {fp, pc}
