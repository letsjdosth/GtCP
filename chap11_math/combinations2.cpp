#include <vector>
#include <iostream>

using namespace std;

//from number_theory2.cpp
long long int effective_pow(int base, int exponent){
    if(exponent==0) return 1;
    long long u = effective_pow(base, exponent/2); //함수선언부의 arg 자료형이 int라서 exponent/2가 0.5가 붙어있을경우 잘려서 들어간다
    //64bit processor-os, 8byte int. -9,223,372,036,854,775,808~9,223,372,036,854,775,807
    u = u*u;
    if(exponent%2==1) u*=base; //exponent/2에서 0.5잘렸을경우 보정
    return u;
}


//노드 n개에 번호를 붙인 서로 다른 트리 개수
int cayley_formula(int node_num){
    return effective_pow(node_num, node_num-2);
}


vector<int> get_prufer_code(vector<vector<int>> adj_list_graph){
    vector<int> prufer_code;
    while(prufer_code.size() < adj_list_graph.size()-2){
        for(int i=0; i<adj_list_graph.size(); i++){ //idx 작은 node부터 반복
            if(adj_list_graph[i].size()==1){
                int stage_prufer_code = adj_list_graph[i][0];
                cout << stage_prufer_code << endl;
                prufer_code.push_back(stage_prufer_code);
                adj_list_graph[i].clear(); //제거할노드는 list size를 0으로 만들자

                //제거한 노드와 연결되있던 노드(==stage_prufer_code인 노드)에서 제거할 노드도 지우자
                auto iter = adj_list_graph[stage_prufer_code].begin();
                while(iter!= adj_list_graph[stage_prufer_code].end()){
                    if(*iter== i) {
                        adj_list_graph[stage_prufer_code].erase(iter);
                        cout << "erase " << *iter << " at node " << stage_prufer_code << endl;
                        break;
                    }
                    else ++iter;
                }
                break;
            }
        }
    }
    return prufer_code;
}

//prufer code와 미완성 그래프를 받아서 전체 그래프를 복원하는 것도 만들수는 있을것같음..
//(새로 붙일 노드 번호를 뭘로 달아야하나에 대해 알고리즘을 좀 생각해보긴해야함)


int main(){
    vector<vector<int>> ex_adj_list(5);
    // 0   1 - 4
    //   \ |
    // 2 - 3

    ex_adj_list[0] = {3};
    ex_adj_list[1] = {3,4};
    ex_adj_list[2] = {3};
    ex_adj_list[3] = {0,1,2};
    ex_adj_list[4] = {1};

    vector<int> ex_prufer_code = get_prufer_code(ex_adj_list);
    cout << "prufer code of ex_adj_list?\n";
    for(auto u : ex_prufer_code){
        cout << u << " ";
    }
    cout << " (true: 3 3 1)" << endl;
}