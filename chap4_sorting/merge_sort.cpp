#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void vector_print(std::vector<int> array){
    for (int i = 0; i < array.size(); i++)
        cout << array[i] << " ";
    cout << endl;
}


//O(n logn)
void conquer(std::vector<int>& array, int left, int mid, int right){
    //merge
    int i, j;
    i = left;
    j = mid + 1;
    
    vector<int> sorted_array(array.size());
    int sorted_idx = left;

    while((i<=mid) && (j<=right)){
        if(array[i]<=array[j]){
            sorted_array[sorted_idx] = array[i];
            sorted_idx++;
            i++;
        } else if(array[i]>array[j]) {
            sorted_array[sorted_idx] = array[j];
            sorted_idx++;
            j++;
        }
    }
    //한쪽이 먼저 끝났을 때 남은 값 처리
    if(i>mid){
        for (int l=j; l<=right; l++){
            sorted_array[sorted_idx] = array[l];
            sorted_idx++;
        }
    } else {
        for (int l=i; l<=mid; l++){
            sorted_array[sorted_idx] = array[l];
            sorted_idx++;
        }
    }
    //원래 array로
    for(int i=left; i<=right; i++){
        array[i] = sorted_array[i];
    }
    
    //for debug
    // cout << "sorted: ";
    // vector_print(sorted_array);
    // cout << "result: ";
    // vector_print(array);

}


void merge_sort(std::vector<int>& array, int left, int right){
    int mid = left + (right - left)/2;
    if(left < right){
        // cout << left << mid << right << endl; //for debug
        merge_sort(array, left, mid);
        merge_sort(array, mid+1, right);
        conquer(array, left, mid, right);
    }
}



int main(){
    vector<int> want_sort = {3,1,8,2,9,2,5,6};
    merge_sort(want_sort, 0, 7);
    vector_print(want_sort);

    vector<int> want_sort2 = {1,5,5,3,3,7,6,1,4};
    merge_sort(want_sort2, 0, 8);
    vector_print(want_sort2);
}
