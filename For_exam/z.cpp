#include <iostream>
#define BUFLEN 16
using namespace std;

int main() {
    int arr[BUFLEN];
    char str[BUFLEN]={'c','o','m','p','u','t','e','r',',','s','y','s','t','e','m',0};
    int *p;
    char *q;
    int i;

    for (i=0; i<BUFLEN; i++)
        arr[i]=BUFLEN -i;

    p=arr+5;
    cout << "*(arr + 12) = "<< *(arr + 12)<< endl;
    cout << "*p = "<< *p << endl;

    q=str+5;
    cout << "q1 = "<< q<< endl;
    *(q+3)=0;
    q=q+4;
    cout << "q2= " << q << endl;
    cout << "str = "<< str << endl;

    return 0;
}