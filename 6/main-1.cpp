#include <iostream>
#include "student.h"
using namespace std;

int main() {
    cout << "h1 >>>" << endl;
    Human *h1 = new Student("Alice", 20, "20240001");
    cout << "h2 >>>" << endl;
    Student *h2 = new Student("Bob", 21, "20230002");
    cout << "h3 >>>" << endl;
    Human *h3 = new Human("Carol", 20);
    h1->print();
    h2->print();
    h3->print();
    return 0;
}
