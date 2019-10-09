#include <iostream>
using namespace std;


//PFArrayD 정의 (기타 참고사항: class의 instance 자체도 c++에선 일종의 dynamic array임)
class PFArrayD{
    private:
        double *a;
        int capacity; //size of the array
        int used; //number of positions in used

    public:
        //constructors(overloaded)
        PFArrayD(); //default capacityValue==50
        PFArrayD(int capacityValue);
        PFArrayD(const PFArrayD& pfaobject); //copy constructor. 즉, 자기 class의 instance를 받으면 복사해 만들어냄
        //이걸 만드는 이유도 복사와 관련있음. 이런게 없으면, c++은 같은타입 인스턴스를 생성자로 받았을 때 같은데를 쳐다보는 포인터를 반환해버림.
        //따라서 같은 값을 다른 메모리위치에 만드는게(즉, deep copy가) 더 적합한 경우엔, 이를 직접 만들어줘야함.
        //(보통 new와 pointer를 사용하는 class정의를 한 경우엔, 무조건 만드는것이 미래 정신건강에 좋을거라고 합니다....)

        void addElement(double element);
        
        bool full() const {
            return (capacity == used);
        }        
        int getCapacity() const {
            return capacity;
        }
        int getNumberUsed() const {
            return used;
        }
        void emptyArray(){
            //empties the array
            used=0;
        }
        double& operator[](int index);

        PFArrayD& operator = (const PFArrayD& rightSide); 
        //= (operator =) overloading (연산자는 override라 안하고 다 overload라 하는듯. arg로 받는 (rvalue의) type을 강조해야 해서 그런가봄)

        ~PFArrayD(); //destructor
};

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




void testPFArrayD();

int main(){
    cout << "This program tests the class PFArrayD.\n";
    char ans;
    do{
        testPFArrayD();
        cout << "Test again? (y/n) ";
        cin >> ans;
    } while ((ans=='y') || (ans=='Y'));
    return 0;
}

void testPFArrayD(){
    int cap;
    cout << "Enter capacity of this super array: ";
    cin >> cap;
    PFArrayD temp(cap);

    cout << "Enter up to " << cap << " nonnegative numbers.\n";
    cout << "Place the negative number at the end.\n";
    double next;
    cin >> next;
    while((next>=0) && !temp.full()){
        temp.addElement(next);
        cin >> next;
    }
    cout << "You entered the following " << temp.getNumberUsed() << " numbers:\n";
    int index;
    int count = temp.getNumberUsed();
    for(index=0; index<count; index++){
        cout << temp[index] << " ";
    }
    cout << endl;
    cout << "(plus a sentinel value.)\n";
}