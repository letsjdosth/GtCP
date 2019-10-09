#include <iostream>
#include "PFArrayD.h"
using namespace std;

bool PFArrayD::full() const {
    return (capacity == used);
}        
int PFArrayD::getCapacity() const {
    return capacity;
}
int PFArrayD::getNumberUsed() const {
    return used;
}
void PFArrayD::emptyArray(){
    //empties the array
    used=0;
}


PFArrayD::PFArrayD() : capacity(50), used(0) { //<-걍 멤버변수값으로 () 안 값이 들어가나봄
    a = new double[capacity];
}

PFArrayD::PFArrayD(int capacityValue): capacity(capacityValue), used(0) {
    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD& pfaobject) : capacity(pfaobject.getCapacity()), used(pfaobject.getNumberUsed()){
    a = new double[capacity];
    for(int i=0; i<used; i++){
        a[i] = pfaobject.a[i];
    }
}

void PFArrayD::addElement(double element){
    if(used >= capacity){
        cout << "Attempt to exceed capacity in PFArrayD.\n";
        exit(0);
    }
    a[used] = element;
    used++;
}

double& PFArrayD::operator[](int index){
    if(index >= used){
        cout << "Illegal index in PFArrayD.\n";
        exit(0);
    }
    return a[index];
}

PFArrayD& PFArrayD::operator = (const PFArrayD& rightSide){ 
    //deep copy를 위해 overloading함 
    //(기본 c++ class내에서 지원하는 =를 쓰면, instance를 가리키는 포인터들이 같은걸 가르키게 되기만 해서
    //다른 메모리공간에 복사가 아닌 참조가 같아지는 형태로 동작함. 때문에 그냥 값만 복사해오도록 아래와 같이 구현
    if (capacity != rightSide.capacity){
        delete [] a; //<-기존거 메모리 잘 리턴하자..
        a = new double[rightSide.capacity];
    }
    capacity = rightSide.capacity;
    used = rightSide.used;
    for(int i=0; i<used; i++){
        a[i] = rightSide.a[i];
    }
    return *this; //<-this: PFArrayD instance를 가리키는 pointer (왜 * 붙여야하지?)
}

PFArrayD::~PFArrayD(){
    //destructor
    delete [] a; 
    //new로 만든 애들(=dynamic variable)은 local scope 나가도 계속 남아있음. 메모리 터뜨리고싶지 않으면 꼭 명시적으로 지워야 함
    //destructor는 class가 스코프를 나갈 때 실행됨
    //여기에 클래스에서 쓴 dynamic variable들 다 삭제하면 메모리 관리가 좀 편해짐
}

