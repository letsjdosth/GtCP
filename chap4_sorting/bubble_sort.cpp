#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//O(n^2)

void bubble_sort(std::vector<int>& array){
    int n = array.size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1; j++){
            if (array[j] > array[j+1]){
                swap(array[j], array[j+1]);
            }
        }
    }
}

void vector_print(std::vector<int> array){
    for (vector<int>::size_type i = 0; i < array.size(); ++i)
        cout << array[i] << endl;
    cout << endl;
}


int main(){
    vector<int> want_sort = {1,3,8,2,9,2,5,6};
    bubble_sort(want_sort);
    vector_print(want_sort);
}
