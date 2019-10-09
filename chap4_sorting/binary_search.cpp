#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void vector_print(std::vector<int> array){
    for (int i = 0; i < array.size(); i++){
        cout << array[i];
    }
    cout << endl;
}

//O(logn)
//search the searching_value using binary search algorithm. Array must be sorted.
int binary_search1(std::vector<int> array, int searching_value){
    //정렬 검사?(걍 검사하느니 찾지...)
    int left = 0;
    int right = array.size() - 1;
    while(left <= right){
        int k = (left + right)/2;
        if(array[k] == searching_value){
            return k;
        } else if(searching_value < array[k]) {
            right = k-1;
        } else {
            left = k+1;
        }
        //해당값이 없으면?<음 처리해야함 귀찮
    }
}

//O(logn)
//search the searching_value using binary search algorithm(type 2). Array must be sorted.
int binary_search2(std::vector<int> array, int searching_value){
    int k = 0;
    int n = array.size() - 1;
    for(int right = n/2; right>=1; right/=2){
        while(k + right < n && array[k+right] <= searching_value){
            k +=right;
        }
    }
    if (array[k] == searching_value){
        return k;
    }
}

int main(){
    int position1, position2;
    vector<int> want_search = {1,3,6,6,9,12,13,15};

    position1 = binary_search1(want_search, 13);
    position2 = binary_search2(want_search, 13);
    cout << "search value: 13, \n" 
    << "searched(by 1): " << want_search[position1] << " of " << position1 <<"-th position.\n"
    << "searched(by 2): " << want_search[position2] << " of " << position2 <<"-th position.\n" << endl;
}
