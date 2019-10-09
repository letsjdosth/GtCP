#include <iostream>

using namespace std;

typedef int* IntPtr;

void fillArray(int a[], int size);
int search(int a[], int size, int target);

int main(){
    cout << "This program searches a list of numbers.\n";

    int arraySize;
    cout << "How many numbers will be on the list? ";
    cin >> arraySize;
    IntPtr a;
    a = new int[arraySize];

    fillArray(a, arraySize);

    int target;
    cout << "Enter a value to search for: ";
    cin >> target;

    int location = search(a, arraySize, target);
    if (location == -1){
        cout << target << " is not in the array.\n";
    } else {
        cout << target << " is element " << location << " in the array.\n";
    }

    delete [] a; //<- memory return 
    // 빈 []를 넣어야 a=int[]가 가리키던 모든 공간을 리턴함. 빼먹으면 음 c++ 컴파일러마다 다르게 동작..
    // delete a[] 도 안된다고함

    return 0;
}

void fillArray(int a[], int size) {
    cout << "Enter " << size << " integers.\n";
    for(int index=0; index<size; index++)
        cin >> a[index];
}

int search(int a[], int size, int target){
    int index = 0;
    while ((a[index]!=target) && (index<size)){
        index++;
    }
    if (index == size) //not in a
        index = -1;
    return index;
}