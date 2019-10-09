#include <iostream>

using namespace std;

int* doubler(int a[], int size);

int main(){
    int a[] = {1,2,3,4,5};
    int *b;

    b = doubler(a, 5);

    int i;
    cout << "Array a:\n";
    for(i=0; i<5; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "Array b:\n";
    for(i=0; i<5; i++){
        cout << b[i] << " "    ;
    }
    cout << endl;

    delete[] b;
    return 0;
}

int* doubler(int a[], int size){
    //주의! dynamic array는 array형태로 return이 안 됨.(컴파일러가 토해냄)
    //포인터로 리턴하자
    int* temp = new int[size];
    for(int i=0; i<size; i++){
        temp[i] = 2 * a[i];
    }
    return temp;
}