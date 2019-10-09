#include <iostream>
#include <vector>
#include <queue>

#include <limits>

using namespace std;

//O(n + mlogm) m:number of edges, n: n round??? <<이거 물어볼것
//priority queue 정렬시간 logm, edge 전체순회 m
int dijkstra(int from, int to, vector<vector<pair<int,int>>> graph_adj_list){
    //warning: should exclude negative weight edge
    int num_nodes = graph_adj_list.size();
    
    priority_queue<pair<int,int>> q; 
    // node x까지의 거리 d가 (-d, x) 형태로 값이 들어감. 최소거리가 맨 처음에 빠지도록 마이너스 붙임
    //(c++ 우선순위큐는 최대값이 처음에 빠지도록 저장된다)
    vector<bool> processed(num_nodes);

    //distance vector 초기화
    vector<int> distance(num_nodes); // from으로부터 idx node까지의 거리
    int INF = std::numeric_limits<int>::max()-1;
    for(int i=0; i<num_nodes; i++){
        distance[i] = INF;
    }
    
    //dijkstra algorithm
    distance[from] = 0;
    q.push({0,from});
    while(!q.empty()){ //priority queue에서 가장 가까운거 뽑아서 거리비교한다
        int processing_node = q.top().second; q.pop();
        if(processed[processing_node]) continue;
        processed[processing_node] = true;
        for(pair<int,int> edge : graph_adj_list[processing_node]){
            int connected_node_with_proc = edge.first;
            int weight = edge.second;
            if(distance[processing_node]+weight < distance[connected_node_with_proc]){
                distance[connected_node_with_proc] = distance[processing_node] + weight;
                q.push({-distance[connected_node_with_proc], connected_node_with_proc});
            }
        }
    }
    return distance[to];
}

int main(){
    //example(adjacency list expression)
    // 0 - (2) -   1 \ 
    // |\          |  \-(5)-\ 
    //(3) \-(7)-\ (3)        4
    // |          \|  /- (2)-/
    // 2 - (1) -   3 /
    vector<vector<pair<int,int>>> adj1(5); //[{connected_node, weight}]
    adj1[0].push_back({1,2}); adj1[0].push_back({2,3}); adj1[0].push_back({3,7});
    adj1[1].push_back({0,2}); adj1[1].push_back({3,3}); adj1[1].push_back({4,5});
    adj1[2].push_back({0,3}); adj1[2].push_back({3,1});
    adj1[3].push_back({0,7}); adj1[3].push_back({1,3}); adj1[3].push_back({2,1}); adj1[3].push_back({4,2});
    adj1[4].push_back({1,5}); adj1[4].push_back({3,2});
    cout << "by dijkstra algorithm. ans:6, return:"<< dijkstra(0, 4, adj1) << endl;
    cout << "by dijkstra algorithm. ans:4, return:"<< dijkstra(0, 3, adj1) << endl;

    //example2
    // 2 - (6) - 3 -\ 
    // |         |   \-(2)-\ 
    //(2)       (9)         4
    // |         |   /-(1)-/
    // 1 - (5) - 0 -/
    vector<vector<pair<int,int>>> adj2(5); //{connected_node, weight}
    adj2[0].push_back({1,5}); adj2[0].push_back({3,9}); adj2[0].push_back({4,1});
    adj2[1].push_back({0,5}); adj2[1].push_back({2,2});
    adj2[2].push_back({1,2}); adj2[2].push_back({3,6});
    adj2[3].push_back({0,9}); adj2[3].push_back({2,6}); adj2[3].push_back({4,2});
    adj2[4].push_back({0,1}); adj2[4].push_back({3,2});
    cout << "by dijkstra algorithm. ans:7, return:"<< dijkstra(0, 2, adj2) << endl;
    cout << "by dijkstra algorithm. ans:3, return:"<< dijkstra(0, 3, adj2) << endl;
}