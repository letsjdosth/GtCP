#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<int> min_sliding_window(vector<int> vec, int window_size){
    int stage_num = vec.size()-window_size+1;
    vector<int> result(stage_num, 0);
    deque<int> deq;
    deque<int> idx_deq; //그냥 deq 하나 만들고 pair<int,int>를 넣자

    //initial stage (첫 윈도우는 다 검사해봐야함)
    int stage=0;
    for(int i=0; i<window_size; i++){
        if(deq.empty()) {
            deq.push_back(vec[i]); idx_deq.push_back(i);
        } else {
            while(1){
                if(!deq.empty() && deq.back() >= vec[i]){
                    deq.pop_back(); idx_deq.pop_back();
                } else {
                    deq.push_back(vec[i]); idx_deq.push_back(i);
                    break;
                }
            }
        }
    }
    result[stage] = deq.front();

    //iteration (추가원소가 작은지/맨앞원소가 윈도우에서 빠졌는지만 검사)
    for(stage = 1; stage<=stage_num; stage++){
        int window_last_idx = stage+window_size-1;
        int window_last_elem = vec[window_last_idx];
        while(!deq.empty() && window_last_elem < deq.back()){
            deq.pop_back(); idx_deq.pop_back();
        }
        while(!idx_deq.empty() && idx_deq.front() < stage){
            deq.pop_front(); idx_deq.pop_front();
        }
        deq.push_back(window_last_elem); idx_deq.push_back(window_last_idx);
        result[stage] = deq.front();
    }

    return result;
}

int main(){
    vector<int> ex_vector = {2,1,4,5,3,4,1,2};
    int ex_window_size = 4;
    vector<int> ex_result_vector = min_sliding_window(ex_vector, ex_window_size);

    
    for(int i=0; i<=ex_vector.size()-ex_window_size; i++){
        cout << "window : ";
        for(int j=0; j<ex_window_size; j++){
            cout << ex_vector[i+j] << " ";
        }
        cout << " -> result : " << ex_result_vector[i] << "\n";
    }
}