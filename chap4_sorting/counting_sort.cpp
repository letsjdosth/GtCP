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


//O(n)
void counting_sort(std::vector<int>& array, int min, int max){
    //for counting vector
    int n = max - min + 1;
    vector<int> counting_vector(n, 0);

    for (int i = 0; i < array.size(); i++){
        int idx = array[i]-min;
        counting_vector[idx]++;
    }
    
    //for result
    vector<int> result_vector;
    for(int i = 0; i < counting_vector.size(); i++) {
        int rep = counting_vector[i];
        for(rep; rep>0; rep--){
            result_vector.push_back(i + min);
        }
    }
    
    for (int i = 0; i < array.size(); i++){
        array[i] = result_vector[i];
    }
}


int main(){
    vector<int> want_sort = {1,3,8,2,9,2,5,6};
    counting_sort(want_sort,1,9);
    vector_print(want_sort);
}
