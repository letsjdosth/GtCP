#include <iostream>
#include <vector>

using namespace std;

int minimum_operate(int limit, vector<int> weight_vector){
    int n = weight_vector.size();
    pair<int, int> best[1<<n]; // 2^n. 부분집합S에 대해 (ride(S)(S일떄 최소운행횟수), last(S)(마지막으로 타는사람의무게합의최소값))
    //pair[s]에서 s의 n번쨰자리 1이면 걔를 포함하는 부분집합을 가리킴
    best[0] = {1,0};
    for(int s=1; s<(1<<n); s++){ //s : subset
        best[s] = {n+1,0}; //initial value. 22에서 처음 min 취할때 무조건 바뀌도록 시작
        for(int p=0; p<n; p++){ //p : individual
            if(s&(1<<p)){ //s가 p를 포함하는 경우 p에대해생각하자...그p를어떻게할지..
                pair<int,int> option = best[s^(1<<p)]; // ^: XOR. 즉 s에서 p만 빠진경우에서 시작
                if(option.second+weight_vector[p] <= limit){
                    option.second += weight_vector[p]; //p 태워보고 limit 안넘으면 추가
                } else {
                    option.first++; //p 태워보고 limit 넘으면 p 그냥 새 운행에 추가
                    option.second = weight_vector[p];
                }
                best[s]=min(best[s], option); //first를기준으로 정렬되는듯???
            }
        }
    }
    return best[(1<<(n)) - 1].first;
}

int main(){
    //for test
    int limit_max = 12;
    vector<int> weight_vector = {2,3,4,5,9};
    int test_result = minimum_operate(limit_max, weight_vector);
    string assert = "F";
    if(test_result == 2) assert = "T";
    cout << "test result : "<< test_result << " (" << assert << ")\n";
  
}