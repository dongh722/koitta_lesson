#include <stdio.h>

int test_func(int a, int b, int c, int d, int e)
{
	return a + b + c + d + e;
}

int main(void)
{
	int a = 1, b = 2, c = 3, d = 4, e = 5, res;

	res = test_func(a, b, c, d, e);
	printf("res = %d\n", res);

	return 0;
}

#if 0
Dump of assembler code for function test_func:
   0x00010438 <+0>:     push    {r11}           ; (str r11, [sp, #-4]!)
   0x0001043c <+4>:     add     r11, sp, #0
   0x00010440 <+8>:     sub     sp, sp, #20
   0x00010444 <+12>:    str     r0, [r11, #-8]
   0x00010448 <+16>:    str     r1, [r11, #-12]
   0x0001044c <+20>:    str     r2, [r11, #-16]
   0x00010450 <+24>:    str     r3, [r11, #-20] ; 0xffffffec
   0x00010454 <+28>:    ldr     r2, [r11, #-8]
   0x00010458 <+32>:    ldr     r3, [r11, #-12]
   0x0001045c <+36>:    add     r2, r2, r3
   0x00010460 <+40>:    ldr     r3, [r11, #-16]
   0x00010464 <+44>:    add     r2, r2, r3
   0x00010468 <+48>:    ldr     r3, [r11, #-20] ; 0xffffffec
   0x0001046c <+52>:    add     r2, r2, r3
   0x00010470 <+56>:    ldr     r3, [r11, #4]
   0x00010474 <+60>:    add     r3, r2, r3
   0x00010478 <+64>:    mov     r0, r3
   0x0001047c <+68>:    sub     sp, r11, #0
   0x00010480 <+72>:    pop     {r11}           ; (ldr r11, [sp], #4)
   0x00010484 <+76>:    bx      lr
End of assembler dump.

Dump of assembler code for function main:
   0x00010488 <+0>:     push    {r11, lr}
   0x0001048c <+4>:     add     r11, sp, #4
   0x00010490 <+8>:     sub     sp, sp, #32
=> 0x00010494 <+12>:    mov     r3, #1
   0x00010498 <+16>:    str     r3, [r11, #-28] ; 0xffffffe4
   0x0001049c <+20>:    mov     r3, #2
   0x000104a0 <+24>:    str     r3, [r11, #-24] ; 0xffffffe8
   0x000104a4 <+28>:    mov     r3, #3
   0x000104a8 <+32>:    str     r3, [r11, #-20] ; 0xffffffec
   0x000104ac <+36>:    mov     r3, #4
   0x000104b0 <+40>:    str     r3, [r11, #-16]
   0x000104b4 <+44>:    mov     r3, #5
   0x000104b8 <+48>:    str     r3, [r11, #-12]
   0x000104bc <+52>:    ldr     r3, [r11, #-12]
   0x000104c0 <+56>:    str     r3, [sp]
   0x000104c4 <+60>:    ldr     r3, [r11, #-16]
   0x000104c8 <+64>:    ldr     r2, [r11, #-20] ; 0xffffffec
   0x000104cc <+68>:    ldr     r1, [r11, #-24] ; 0xffffffe8
   0x000104d0 <+72>:    ldr     r0, [r11, #-28] ; 0xffffffe4
   0x000104d4 <+76>:    bl      0x10438 <test_func>
   0x000104d8 <+80>:    str     r0, [r11, #-8]
   0x000104dc <+84>:    ldr     r1, [r11, #-8]
   0x000104e0 <+88>:    ldr     r0, [pc, #16]   ; 0x104f8 <main+112>
   0x000104e4 <+92>:    bl      0x102e0 <printf@plt>
   0x000104e8 <+96>:    mov     r3, #0
   0x000104ec <+100>:   mov     r0, r3
   0x000104f0 <+104>:   sub     sp, r11, #4
   0x000104f4 <+108>:   pop     {r11, pc}
   0x000104f8 <+112>:   andeq   r0, r1, r12, ror #10

위 코드를 보면 스택에 저장해놓은 값을 활용한다.
나머지는 r0 ~ r3 레지스터가 활용되고 있음을 볼 수 있다.
실제 스택에서 값을 뽑아오는 부분은 아래에 해당한다.

   0x00010470 <+56>:    ldr     r3, [r11, #4]
   0x00010474 <+60>:    add     r3, r2, r3

#endif
