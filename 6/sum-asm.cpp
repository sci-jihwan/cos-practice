#include <iostream>
using namespace std;

int decode1(long *xp, long *yp, long *zp) {
    __asm__(
        // "endbr64\n"
        // "push %rbp\n"
        // "mov %rsp,%rbp\n"
        // "mov %edi,-0x4(%rbp)\n"
        // "mov %esi,-0x8(%rbp)\n"
        // "mov -0x4(%rbp),%edx\n"
        // "mov -0x8(%rbp),%eax\n"
        // "add %edx,%eax"
        "movq (%rdi), %r8\n"
        "movq (%rsi), %rcx\n"
        "movq (%rdx), %rax\n"
        "movq %r8, (%rsi)\n"
        "movq %rcx (%rdx)\n"
        "movq %rax, %(rdi)\n"

        // "add %esi, %edi \n"
        // "mov %edi, %eax"
    );
}

int main () {
    // int a, b, c;
    // a=3; b=5;
    // c=sum(a,b);
    // cout <<"c:"<< c <<endl;
    
    long x,y,z;
    x=10000; y=20000; z=30000;
    cout << "before decode1(): "<< "x: "<< x << "y: "<< y << "z: "<< z << endl;
    decode1(&x, &y, &z);
    cout << "after decode1(): "<< ", x: "<< x << ", y: "<< y << ", z: "<< z << endl;
    return 0;
}