#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    int num1, num2;
       if (argc == 3) {
        num1 = std::atoi(argv[1]);
        num2 = std::atoi(argv[2]);
    } else {
        std::cout << "Enter two numbers: ";
        std::cin >> num1 >> num2;
    }
    
    // 두 번째 숫자가 첫 번째 숫자보다 커야 함
    if (num2 <= num1) {
        std::cout << "The second number must be greater than the first number. Exiting...\n";
        return 1;
    }
    
    // 숫자 합산
    int sum = 0;
    for (int i = num1; i <= num2; ++i) {
        sum += i;
    }
    
    // 결과 출력
    std::cout << "Sum from " << num1 << " to " << num2 << " is: " << sum << "\n";
    return 0;
}