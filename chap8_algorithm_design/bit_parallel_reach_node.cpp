#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

// 8.1.3 counting reachable node in graph
vector<int> reach_func(vector<vector<int>> adj_list_graph){
    int num_node = adj_list_graph.size(); //if num_node>8, then modify the bitset<n> to n>8
    vector<int> result(num_node);
    vector<bitset<8>> reach;
    for(int proc_node=0; proc_node<num_node; proc_node++){
        bitset<8> temp(0);
        reach.push_back(temp); //어차피 포인터로넘어가서 for문 밖으로 나가도 안꺠지나봄
        reach[proc_node][proc_node] = 1;
    }
    for(int proc_node=num_node-1; proc_node>=0; proc_node--){ 
        //여기도 엄밀히하려면 그래프 노드를 역순으로 돌아야함. 하지만 음... adj list에서는 역순 찾는데 한세월 걸린다..
        for(auto next_node: adj_list_graph[proc_node]){
            reach[proc_node] |= reach[next_node];
        }
    }
    for(int proc_node=0; proc_node<num_node; proc_node++){
        result[proc_node] = reach[proc_node].count();
    }
    return result;
}


int main(){
    //ex graph
    // 0 -> 1 -\ 
    // |    |   > 4
    // v    v    ^
    // 2 -> 3 - /
    vector<vector<int>> graph_ex(5);
    graph_ex[0] = {1,2};
    graph_ex[1] = {3,4};
    graph_ex[2] = {3};
    graph_ex[3] = {4};
    graph_ex[4] = {};

    vector<int> reach_result;
    reach_result = reach_func(graph_ex);

    cout << "reach! \nfrom: 0 1 2 3 4 \nto  : ";
    for(int i=0; i<5; i++){
        cout <<  reach_result[i] << " ";
    }
    cout << endl;
}

