#include <iostream>

using namespace std;

struct Record{
    int number;
    char grade;
};

class Sample{
    private:
        int stuff = 1;
    
    public:
        void showStuff() const{
            cout << this->stuff << endl; //this: this를 부르는 calling object 자체를 가리키는 pointer (python으로 치면 일종의 &self)
            //기타: 굳이 이렇게 쓸 필요 없음. c++에선 클래스 정의 내에서면 stuff를 바로 부르면 됨
        }
};

int main(){
    // -> (arrow) operator
    Record *p;
    p = new Record; //struct나 class를 포인터로 선언해두고
    p ->number = 2001; //그 struct나 class의 멤버에 접근할 때 ->를 사용
    p ->grade = 'A'; //즉, (*p).grade 와 p->grade 가 같음


}

