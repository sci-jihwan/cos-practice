#include <iostream>
#include "human.h"
using namespace std;

int main () {
    Human *hw;
    hw = new Human("Jihwan Kim");
    hw->print();
    hw->setAge(21);
    hw->print();
}