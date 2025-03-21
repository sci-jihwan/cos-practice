#include<iostream>

int main(int argc, char *argv[])
{
    int x{};    // unsigned int x {};로 바꿀 경우 최대값에서 2를 뺀값으로 출력, 즉 의도하지 않은 방향으로 출력될거임.
    std::cout << "Enter a number: ";
    std::cin >> x;

    if (x>=0){
        std::cout <<" You entered a positive integer!" << std::endl;
    } else{
        std::cout <<"You entered a negative integer!" << std::endl;
    }    
    return 0;
}