#include <iostream>
#include <vector>

using namespace std;

//O(mn)
bool knapsack_possible(int x, vector<int> weight){
    if(x==0) return true;
    int weight_size= weight.size();
    vector<vector<bool>> possible(weight_size+1, vector<bool>(x+1,false));
//                      j=0 1 2 3 ... x 
//  k=0                   1 0 0 0 ....0
//  k=1(ex.weight[k]=2)   1 0 1 0 ... 0
//   ...
//  k=weight.size         1 0 1 ...   ?
//     
    possible[0][0]=true;
    for(int k=1; k<=weight_size; k++){ // weight가 (0,weight)로 변했다고 생각. (맨 앞 열(0 해당)떄문에 인덱스가 1씩 밀려야함)
        for(int j=0; j<=x; j++){
            if(j-weight[k-1] >= 0){
                possible[k][j] = possible[k-1][j-weight[k-1]] || possible[k][j]; //여기도 weight[k-1]
            }
            possible[k][j] = possible[k-1][j] || possible[k][j];
        }
    }
    return possible[weight_size][x];
}

//O(n)
bool efficient_knapsack_possible(int x, vector<int> weight){
    vector<int> possible(x+1, false);
    possible[0]=true;
    for(int k=0; k<weight.size(); k++){
        for(int j=x-weight[k]; j>=0; j--){
            possible[j+weight[k]] = possible[j] || possible[j+weight[k]];
        }
    }
    return possible[x];
}

int main(){
    vector<int> test_weight_vector = {1,3,3,5};
    vector<bool> assert_vector = {1,1,0,1,1,1,1,1,1,1,0,1,1};

    //test
    for(int i=0; i<=12; i++){
        int possible_result = knapsack_possible(i, test_weight_vector); 
        string assert = "F";
        if(possible_result==assert_vector[i]) assert = "T";
        cout << "x="<< i <<" : possible? "<< possible_result << " " << assert << endl;

    }

    for(int i=0; i<=12; i++){
        int possible_result = efficient_knapsack_possible(i, test_weight_vector); 
        string assert = "F";
        if(possible_result==assert_vector[i]) assert = "T";
        cout << "x="<< i <<" : possible? "<< possible_result << " " << assert << endl;
    }
}