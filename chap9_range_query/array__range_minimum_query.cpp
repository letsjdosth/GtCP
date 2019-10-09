#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

//9.1.1
//sparse table algorithm (Bender-Farach-Colton's)
//구간길이가 2^k인 경우의 minimum을 다 구해두자
//자기 idx를 시작으로, 뒤로 2^k만큼 구해서 매트릭스 만들자

//O(nlogn)
vector<vector<int>> get_minvalue_sparse_mat(std::vector<int> vec){
    int size = vec.size();
    vector<vector<int>> sparse_mat;
    int k = 1;
    while(pow(2,k)<= size){
        //2^k구간 벡터 만들어서 sparse_mat에 넣자
        vector<int> for_2_power_k_vec(size, 0);
        for(int i=0; i<= size - pow(2,k); i++){
            int stage_min = vec[i];
            for(int j=1; j<pow(2,k); j++){
                if(stage_min > vec[i+j]){
                    stage_min = vec[i+j];
                }
            }
            for_2_power_k_vec[i] = stage_min;
        }
        sparse_mat.push_back(for_2_power_k_vec);
        k++;
    }
    return sparse_mat;
}

//O(1)
int min_by_sparse_table_algorithm(int from, int to, vector<vector<int>> sparse_mat){
    int k = 0;
    int min;

    //2^k가 to-from+1을 초과하지 않는 최고 k
    while(pow(2,k) < (to-from+1)){
        cout << k << endl;
        k++;
    }
    k--;
    //k <= 1 이면 이자리에서 에러내자
    
    //비교
    cout << k << endl;
    int search_length = pow(2,k);
    int length_2powerk_head_min = sparse_mat[k-1][from];
    int length_2powerk_tail_min = sparse_mat[k-1][to-search_length+1];
    if(length_2powerk_head_min<length_2powerk_tail_min)
        min = length_2powerk_head_min;
    else min = length_2powerk_tail_min;
    return min;
}

int main(){
    vector<int> ex_vector = {1,3,4,8,6,1,4,2};
    vector<vector<int>> ex_sparse_mat = get_minvalue_sparse_mat(ex_vector);
    int result_min = min_by_sparse_table_algorithm(1, 6, ex_sparse_mat);

    int k = 1;
    for(auto u : ex_sparse_mat){
        cout << "for length" << pow(2,k) << " : ";
        for(auto v : u){
            cout << v << " ";
        }
        cout << "\n";
        k++;
    }
    cout << "result minimum of range [1,6] : " << result_min << " (true: 1)";
    
}