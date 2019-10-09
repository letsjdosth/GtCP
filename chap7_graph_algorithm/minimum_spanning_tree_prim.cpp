#include <vector>
#include <queue>
#include <tuple>

#include <iostream>
#include <limits>

using namespace std;


int prim(vector<vector<pair<int,int>>> graph_adj_list, int start_node = 0){
    //warning: should exclude negative weight edge
    //graph_adj_list의 0번째부터 쓸 것
    int num_nodes = graph_adj_list.size();
    
    int weight_sum = 0;
    vector<int> link; 
    vector<bool> connect_status(num_nodes, false);
    for(int i=0; i<num_nodes; i++) link.push_back(i);

    bool all_connected = false;
    

    
    int iter =0;
    while(!all_connected){
        
        connect_status[proc_node] = true;
        
        bool loop_flag = true;
        while(loop_flag){ //위 시작점에서 시작하여 연결
        //comment: 이게 아니다. 이어진 모든 노드에서 가장 최소 edge에서 가장 작은 weight edge를 포함한다
            priority_queue<pair<int,int>> q;
            for(int i=0; i<graph_adj_list[proc_node].size(); i++){
                int conn_node = graph_adj_list[proc_node][i].first;
                int weight = graph_adj_list[proc_node][i].second;
                q.push({-weight, conn_node});
            }
            while(1){ //proc_node에서 다음 고르기
                if(q.empty()){
                    connect_status[proc_node] = true;
                    loop_flag = false;
                    break;
                }
                int next_node = q.top().second; 
                int w = -q.top().first;
                q.pop();
                if(connect_status[next_node]) continue;
                link[proc_node] = next_node;
                connect_status[proc_node] = true;
                weight_sum += w;
                proc_node = next_node;
                break;
            }    
        }
        //isolated node 처리해야한다 (예에서는 index 3) <-음 어케해야할지모르겠다
        //지금 실제로 3에서 5로 오는 weight 7 이 안더해지고있음
        int last_proc = proc_node;
        for(int i=0; i <connect_status.size(); i++){
            if(!connect_status[i]) proc_node = i;
        }
        if(last_proc==proc_node) all_connected = true;
    }
    

    //for debug
    cout << "node ";
    for(int i=0; i<num_nodes; i++){
        cout << i << " ";
    }
    cout << "\nproc ";
    for(int elem : connect_status){
        cout << elem << " ";
    }
    cout << "\nlink ";
    for(int elem : link){
        cout << elem << " ";
    }
    cout << "\n";
    return weight_sum;
}

int main(){
    //adj list expression
    //      (3) - 1 - (5) - 2 - (9) 
    //      /     |         |     \ 
    //   0 -     (6)       (3)     - 3
    //      \     |         |     / 
    //      (5) - 4 - (2) - 5 - (7)
    vector<vector<pair<int,int>>> weighted_adj(6);
    weighted_adj[0].push_back({1,3}); weighted_adj[0].push_back({4,5}); 
    weighted_adj[1].push_back({0,3}); weighted_adj[1].push_back({2,5}); weighted_adj[1].push_back({4,6});
    weighted_adj[2].push_back({1,5}); weighted_adj[2].push_back({3,9}); weighted_adj[2].push_back({5,3}); 
    weighted_adj[3].push_back({2,9}); weighted_adj[3].push_back({5,7});
    weighted_adj[4].push_back({0,5}); weighted_adj[4].push_back({1,6}); weighted_adj[4].push_back({5,2});
    weighted_adj[5].push_back({2,3}); weighted_adj[5].push_back({3,7}); weighted_adj[5].push_back({4,2}); 
    
    cout << prim(weighted_adj) << " (true:20)" << endl;

}