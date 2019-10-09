#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//O(n)
vector<int> finding_subvector(vector<int> vec, int target_val){
    int left_pointer = 0;
    int right_pointer = 0;
    while(right_pointer < vec.size()){
        int stage_sum = 0;
        for(int i=left_pointer; i<=right_pointer; i++){
            stage_sum += vec[i];
        }
        if(stage_sum == target_val) break;
        else if (stage_sum>target_val){
            left_pointer++;
        } else {
            right_pointer++;
        }
    }
    
    vector<int> result;
    if(right_pointer<vec.size()){
        for(int i=left_pointer; i<=right_pointer; i++){
            result.push_back(vec[i]);
        }
    } else {
        result = {};
    }
    return result;
}

vector<int> finding_two_sum(vector<int>& vec, int target_val){
    //이 함수 코드의 문제: vec이 sorting이 안되어있을경우 외부의 vec을 수정함
    //사실 & 안 붙여 받아도 아래 코드는 멀정히 돌아가지만, 2point method가 찾는 index는 sorting 이후의 것에 해당하므로
    //이를 sorting 전과 매치해주는 코드가 추가로 필요함
    //음근데귀찮다...
    int left_pointer = 0;
    int right_pointer = vec.size()-1;

    //sort the vector <- depend on <algorithm>
    sort(vec.begin(), vec.end());

    while(left_pointer != right_pointer){
        int stage_sum;
        while(1){
            stage_sum = vec[left_pointer] + vec[right_pointer];
            if(stage_sum > target_val) right_pointer--;
            else break;
        }
        if(stage_sum == target_val) break;
        else left_pointer++;
    }

    vector<int> result;
    if(left_pointer < right_pointer){
        result.push_back(left_pointer);
        result.push_back(right_pointer);
    } else {
        result = {};
    }
    return result;
}


int main(){
    //example1
    vector<int> ex1_vector = {1,3,2,5,1,1,2,3};
    vector<int> ex1_subvec8 = finding_subvector(ex1_vector, 8);
    vector<int> ex1_2sum8 = finding_two_sum(ex1_vector, 8);
    cout << "result subvector (sum 8): ";
    for(int u : ex1_subvec8){
        cout << u << " ";
    }
    cout << endl;
    cout << "result 2sum (sum 8): "
    << "(caution: since the argument vector is sorted by finding_two_sum, index can be changed with original ones.)\n"
    << "index: ";
    for(int i=0; i<2; i++){
        cout << ex1_2sum8[i] << " ";
    }
    cout << "with value: ";
    for(int i=0; i<2; i++){
        cout << ex1_vector[ex1_2sum8[i]] << " ";
    }
    cout << endl;
    
    //example2
    vector<int> ex2_vector = {1,4,5,6,7,9,9,10};
    vector<int> ex2_subvec15 = finding_subvector(ex2_vector, 15);
    vector<int> ex2_2sum12 = finding_two_sum(ex2_vector, 12);
    cout << "result subvector (sum 15): ";
    for(int u : ex2_subvec15){
        cout << u << " ";
    }
    cout << endl;
    cout << "result 2sum (sum 12): "
    << "(caution: since the argument vector is sorted by finding_two_sum, index can be changed with original ones.)\n"
    << "index: ";
    for(int i=0; i<2; i++){
        cout << ex2_2sum12[i] << " ";
    }
    cout << "with value: ";
    for(int i=0; i<2; i++){
        cout << ex2_vector[ex2_2sum12[i]] << " ";
    }
    cout << endl;
}