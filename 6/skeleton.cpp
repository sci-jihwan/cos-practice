#include <iostream>
using namespace std;

int run()
{
    __asm__(
        "movq $100, %rax"
    );
    // 원래는 리턴값을 줘야하지만 그냥 리턴이 없으면 컴파일러는 그 안에 있는 값을 주면 되겠구나 생각함.
}

int main()
{
    cout << "The skeleton code for the assembly language" << endl;
    cout << "return value: " << run() <<endl;
    return 0;
}