#include <iostream>

using namespace std;


// 8.1.1. Hamming distance
int hamming(int a, int b){
    return __builtin_popcount(a^b);
}

// ex
int main(){
    // {00111, 01101, 11110}, 최소헤밍거리?
    int elem1 = 7, elem2 = 13, elem3 = 30;
    cout << hamming(elem1, elem2) << endl;
    cout << hamming(elem1, elem3) << endl;
    cout << hamming(elem2, elem3) << endl;
    //-> 2 !

}