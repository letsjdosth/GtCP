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
        
        bool full() const;
        int getCapacity() const;
        int getNumberUsed() const;
        void emptyArray();
        double& operator[](int index);

        PFArrayD& operator = (const PFArrayD& rightSide); 
        //= (operator =) overloading (연산자는 override라 안하고 다 overload라 하는듯. arg로 받는 (rvalue의) type을 강조해야 해서 그런가봄)

        ~PFArrayD(); //destructor
};
