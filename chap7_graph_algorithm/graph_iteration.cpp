#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;


// ~~ iteration by depth-first search(DFS) ~~
void dfs_algorithm(int s, vector<vector<int>> graph_adj_list, vector<bool>& visited){
    //함수에 넘기는 s는 시작점임
    //재귀구조로 순회 (<-음.. for문으로 바꾸면 응용시 가져다쓸때 더 쉬울것같다)
    if(visited[s]) return;
    //when s visiting,
    visited[s] = true;
    cout << "now, visiting the node : " << s << endl;
    //go next step
    for(auto u: graph_adj_list[s]){
        dfs_algorithm(u, graph_adj_list, visited);
    }
}

void dfs(vector<vector<int>> graph_adj_list, int start_node=0){
    //재귀구조로 넘기기 전 작업 수행 후 dfs_algorithm을 호출 
    int node_num = graph_adj_list.size();
    vector<bool> visited(node_num);
    dfs_algorithm(start_node, graph_adj_list, visited);

}

void dfs_using_stack(vector<vector<int>> graph_adj_list, int start_node=0){
    int node_num = graph_adj_list.size();
    stack<int> q; //순회순서를 들고있을 큐(선입선출). 시작 노드와의 거리가 증가하는 순서대로 들어감.
    vector<bool> visited(node_num);

    //at starting node
    visited[start_node] = true;
    vector<int> distance(node_num);
    distance[start_node] = 0;
    q.push(start_node);

    while(!q.empty()){
        //when visiting node s (queue 최고우선순번)
        int s= q.top(); q.pop();
        cout << "now, visiting the node : " << s << endl;

        //go to next
        for (auto u : graph_adj_list[s]){
            if(visited[u]) continue;
            visited[u] = true;
            distance[u] = distance[s] + 1;
            q.push(u);
        }
    }
    return;
}


// ~~ iteration by Breadth-first search(BFS) ~~
void bfs(vector<vector<int>> graph_adj_list, int start_node=0){
    int node_num = graph_adj_list.size();
    queue<int> q; //순회순서를 들고있을 큐(선입선출). 시작 노드와의 거리가 증가하는 순서대로 들어감.
    vector<bool> visited(node_num);

    //at starting node
    visited[start_node] = true;
    vector<int> distance(node_num);
    distance[start_node] = 0;
    q.push(start_node);

    while(!q.empty()){
        //when visiting node s (queue 최고우선순번)
        int s= q.front(); q.pop();
        cout << "now, visiting the node : " << s << endl;

        //go to next
        for (auto u : graph_adj_list[s]){
            if(visited[u]) continue;
            visited[u] = true;
            distance[u] = distance[s] + 1;
            q.push(u);
        }
    }
    return;
}

bool is_connected(vector<vector<int>> graph_adj_list){
    //연결그래프(어느 노드에서 시작해도 모든 노드를 다 방문할 경로를 찾을 수 있는 있는 그래프)인지 확인
    //dfs 사용
    int node_num = graph_adj_list.size();
    vector<bool> visited(node_num);
    for(int i; i<node_num; i++){
        visited.clear(); //<여기있는게 맞나?
        dfs_algorithm(i, graph_adj_list, visited);
        bool is_no_visit = *min_element(visited.begin(), visited.end()); // 최소값으로 visited에 0 있나 확인함 (개선법?)
        if(is_no_visit == 0) return false;
    }
    return true;
}

bool is_cyclic_dfs_algorithm(int s, vector<vector<int>> graph_adj_list, vector<bool>& visited, int last_node){
    //재귀구조로 순회
    if(visited[s] && s!=last_node) return true; // 새로 방문한 노드에 visited가 true인 곳으로 가는 길이 있으면, 이는 cycle이 있다는 것임
    //when s visiting,
    visited[s] = true;
    int new_last_node = s;
    //go next step
    for(auto u: graph_adj_list[s]){
        if(u==last_node) continue; // (기존것으로 돌아가면 위 75줄의 if문이 무조건 true됨. 
        bool recur_result = is_cyclic_dfs_algorithm(u, graph_adj_list, visited, new_last_node);
        if(recur_result) return true; // 재귀 스택 하나 걷어내며 true 보냄
    }
    return false;
}
bool is_cyclic(vector<vector<int>> graph_adj_list, int start_node = 0){
    //그래프에 cycle이 있는지 확인
    //dfs 사용
    int node_num = graph_adj_list.size();
    vector<bool> visited(node_num);
    int last_node = -1; //node 인덱스 바깥값을 주자
    bool result = is_cyclic_dfs_algorithm(start_node, graph_adj_list, visited, last_node);
    return result;
}

bool is_bipartite_dfs_algorithm(int s, vector<vector<int>> graph_adj_list, vector<int>& visited, int last_color){
    //재귀구조로 순회
    if(visited[s] && visited[s]==last_color){
        return false;
    } else if(visited[s]) {
        return true;
    }
    //when s visiting,
    int this_step_color;
    if (last_color==1){
        this_step_color = 2;
    } else {
        this_step_color = 1;
    }
    visited[s] = this_step_color;
    
    //go next step
    for(auto u: graph_adj_list[s]){
        int result = is_bipartite_dfs_algorithm(u, graph_adj_list, visited, this_step_color);
        if(!result) return false;
    }
    return true;
}

bool is_bipartite(vector<vector<int>> graph_adj_list, int start_node = 0){
    int node_num = graph_adj_list.size();
    vector<int> visited_and_color(node_num); // 0:unvisited 1:color1 2:color2
    bool result = is_bipartite_dfs_algorithm(start_node, graph_adj_list, visited_and_color, -1);
    return result;
}


int main(){
    //example graph: adjacency list expression
    //ex1. connected, cyclic, not bipartite
    //  1 - 2 -\ 
    //  |   |   3
    //  4   5 -/
    vector<vector<int>> adj(5);
    adj[1-1].push_back(2-1); adj[1-1].push_back(4-1);
    adj[2-1].push_back(1-1); adj[2-1].push_back(3-1); adj[2].push_back(5-1);
    adj[3-1].push_back(2-1); adj[3-1].push_back(5-1);
    adj[4-1].push_back(1-1);
    adj[5-1].push_back(2-1); adj[5-1].push_back(3-1);

    //ex2. not connected, is cyclic, not bipartite
    // 0-2-3  1
    // |   |  |
    // \---/  4
    vector<vector<int>> adj2(5);
    adj2[0].push_back(2); adj2[0].push_back(3);
    adj2[1].push_back(4);
    adj2[2].push_back(0); adj2[2].push_back(3);
    adj2[3].push_back(0); adj2[0].push_back(2);
    adj2[4].push_back(1);

    //ex3. is connected, not cyclic, bipartite
    // 0 - 1 - 2
    //   \-3 - 4 - 6
    //       \-5
    vector<vector<int>> adj3(7);
    adj3[0].push_back(1); adj3[0].push_back(3);
    adj3[1].push_back(0); adj3[1].push_back(2);
    adj3[2].push_back(1);
    adj3[3].push_back(0); adj3[3].push_back(4); adj3[3].push_back(5);
    adj3[4].push_back(3); adj3[4].push_back(6);
    adj3[5].push_back(3);
    adj3[6].push_back(4);

    cout << "~example1~~" << endl;
    dfs(adj);
    bfs(adj);
    dfs_using_stack(adj);
    cout << "connected graph? " << is_connected(adj) << endl;
    cout << "cyclic graph? " << is_cyclic(adj) << endl;
    cout << "bipartite graph ?" << is_bipartite(adj) << endl;
    

    cout << "~example2~~" << endl;
    dfs(adj2);
    bfs(adj2);
    dfs_using_stack(adj2);
    cout << "connected graph? " << is_connected(adj2) << endl;
    cout << "cyclic graph? " << is_cyclic(adj2) << endl;
    cout << "bipartite graph? " << is_bipartite(adj2) << endl;

    cout << "~example3~~" << endl;
    dfs(adj3);
    bfs(adj3);
    dfs_using_stack(adj3);
    cout << "connected graph? " << is_connected(adj3) << endl;
    cout << "cyclic graph? " << is_cyclic(adj3) << endl;
    cout << "bipartite graph? " << is_bipartite(adj3) << endl;
}

