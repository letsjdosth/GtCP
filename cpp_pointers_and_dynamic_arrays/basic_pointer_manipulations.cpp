#include <iostream>

using namespace std;

int main(){
    int *p1, *p2;

    p1 = new int; //<- new type : 해당 type variable을 메모리 어딘가에 만들고 그 포인터 반환 (*p1이 해당 type으로 선언되어 있어야 함)
    *p1 = 42;
    p2 = p1;
    cout << "*p1 == " << *p1 << endl; //42
    cout << "*p2 == " << *p2 << endl; //42

    *p2 = 53;
    cout << "*p1 == " << *p1 << endl; //53
    cout << "*p2 == " << *p2 << endl; //53

    p1 = new int;
    *p1 = 88;
    cout << "*p1 == " << *p1 << endl; //88
    cout << "*p2 == " << *p2 << endl; //53
    

    cout << "Hope you get the point of this example!\n";
    return 0;
}