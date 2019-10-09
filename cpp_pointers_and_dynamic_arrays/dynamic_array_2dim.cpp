#include <iostream>

using namespace std;

typedef int* IntArrayPtr;

int main(){
    int d1, d2;
    cout << "Enter the row and column dimensions of the array:\n";
    cin >> d1 >> d2;

    //2dim dynamic array (dim: d1 * d2) 선언
    IntArrayPtr *m = new IntArrayPtr[d1]; //<-pointer를 담을 array라서 *가 2개붙나봄..(?)
    int i, j;
    for (i=0; i<d1; i++){
        m[i] = new int[d2]; //<-여긴 *m 아님. 그냥 각 row 시작점으로 address를 옮기는 것
    }

    //순회 및 접근
    cout << "Enter " << d1 << " rows of " << d2 << " integers each:\n";
    for(i=0; i<d1; i++){
        for(j=0; j<d2; j++){
            cin >> m[i][j];
        }
    }

    cout << "Echoing the two-dimensional array:\n";
    for(i=0; i<d1; i++){
        for(j=0; j<d2; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    
    //메모리 리턴
    for(i=0; i<d1; i++){
        delete[] m[i]; //<-안에들은것도 다 지워주자
    }
    delete[] m;


}