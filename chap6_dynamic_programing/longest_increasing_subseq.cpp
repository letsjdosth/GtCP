#include <iostream>
#include <vector>

using namespace std;

//find longest increasing subsequence in range of given array(0,k)
int len_longest_incr_subseq(int k, vector<int> array){
    vector<int> length(k+1);
    for(int i=0; i<=k; i++){
        length[i] = 1;
        for(int j=0; j<i; j++){ //array의 j번째 값이 지금것보다 작으면 1 더해보자
            if(array[j] < array[i]){
                length[i] = max(length[i], length[j]+1);
            }
        }
    }
    return length[k];
}

int main(){
    vector<int> test_vector = {6,2,5,1,7,4,8,3};
    vector<int> assert_vector = {1,1,2,1,3,2,4,2};
    for(int i=0; i<=7; i++){
        int len_result = len_longest_incr_subseq(i, test_vector);
        string assert = "F";
        if(len_result==assert_vector[i]) assert = "T";
        cout << "x="<< i <<" : length="<< len_result << " " << assert << endl;

    }
}