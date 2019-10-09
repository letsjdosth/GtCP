#include <iostream>

using namespace std;

typedef int* IntPtr;

int main(){
    IntPtr p;
    int a[10];
    int index;

    for (index = 0; index < 10 ; index++){
        a[index] = index;
    }
    
    p = a; //<-array variable은 첫 위치를 pointer처럼 주소로 들고있으므로, 호환됨. 
    //단, a = p는 안됨. array로 선언된 변수는 그냥 array로만 쓰도록 강제되어 있음.

    for (index = 0; index < 10; index++){
        cout << p[index] << " ";
    }
    cout << endl;

    for (index = 0; index < 10; index++){
        p[index] = p[index] + 1;
    }

    for (index = 0; index < 10; index++){
        cout << a[index] << " ";
    }
    cout << endl;

    return 0;
}