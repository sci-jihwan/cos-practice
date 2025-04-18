#include <iostream>
using namespace std;

short test(short x, short y, short z)
{
    __asm__(
        "leaq	(%rdx, %rsi), %rax\ㅜ"
        "subq	%rdi, %rax"
        cmpq	$5, %rdx
        jle	.L2
        cmpq	$2, %rsi
        jle	.L3
        movq	%rdi, %rax
        idivq	%rdx, %rax
        "
    ret

    )
}