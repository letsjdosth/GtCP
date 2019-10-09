#include <vector>
#include <iostream>

using namespace std;

vector<int> vector_return(int a, int b){
    vector<int> temp;
    temp.push_back(a);
    temp.pop_back();
    
    return temp;
}

int main(){
    int a = 42;
    cout << &a << endl;
}