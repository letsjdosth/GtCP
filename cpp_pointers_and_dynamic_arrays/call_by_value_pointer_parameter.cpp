#include <iostream>

using namespace std;

typedef int* intPointer;

void sneaky(intPointer temp);

int main(){
    intPointer p;

    p = new int;
    *p = 77;

    cout << "Before call to function *p == " << *p << " at " << p  << endl;

    sneaky(p);

    cout << "After call to function *p == " << *p << " at " << p  << endl;
    return 0;
}

void sneaky(intPointer temp){ //reference(memory address)가 넘어간다
    *temp = 99;
    cout << "Inside functioon call *temp == " << *temp << endl;
}