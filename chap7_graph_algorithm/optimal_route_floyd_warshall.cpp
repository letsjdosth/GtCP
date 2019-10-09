#include <iostream>
#include <vector>
#include <limits>

using namespace std;

//O(n^3)
int floyd_warshall(int from, int to, vector<vector<int>> graph_adj_matrix){
    int num_nodes = graph_adj_matrix.size();

    //INF with protecting overflow
    int INF = std::numeric_limits<int>::max()/2-1; 
    // <-뒤에서 임의의 값 2개를 더한것이 overflow가 되어 마이너스가 되면 min이 맛가게 동작
    // 때문에 더해서 overflow 안 나는 최대값을 준다
    // (예상되는 문제: weight가 이 INF값보다 크면 엿같아짐. 나중에 WEIGHT가 너무크면 에러뱉는 코드를 넣던가 할것)
    //다른해결책? 빅인트?


    //dist matrix initialize
    vector<vector<int>> dist_matrix(num_nodes, std::vector<int>(num_nodes));
    for(int i=0; i<num_nodes; i++){
        for(int j=0; j<num_nodes; j++){
            if(i==j) dist_matrix[i][j]=0;
            else if (graph_adj_matrix[i][j]) dist_matrix[i][j] = graph_adj_matrix[i][j];
            else dist_matrix[i][j] = INF;
        }
    }
    // cout << dist_matrix[0][0] << " " << dist_matrix[0][1] << " " << dist_matrix[0][2] << "\n";

    //floyd_warshall algorithm
    for(int mid_node=0; mid_node<num_nodes; mid_node++){
        for(int i=0; i<num_nodes; i++){
            for(int j=0; j<num_nodes; j++){
                dist_matrix[i][j] = min(dist_matrix[i][j], dist_matrix[i][mid_node] + dist_matrix[mid_node][j]);
            }
        }
    }
    return dist_matrix[from][to];
}


int main(){
    //example(adjacency matrix expression)
    // 2 - (7) - 3 -\ 
    // |         |   \-(2)-\ 
    //(2)       (9)         4
    // |         |   /-(1)-/
    // 1 - (5) - 0 -/
    vector<vector<int>> adj_matrix(5,{0,0,0,0,0});
    adj_matrix[0] = {0,5,0,9,1};
    adj_matrix[1] = {5,0,2,0,0};
    adj_matrix[2] = {0,2,0,7,0};
    adj_matrix[3] = {9,0,7,0,2};
    adj_matrix[4] = {1,0,0,2,0};
    cout << "by floyd-warshall algorithm. ans:7, return:"<< floyd_warshall(0, 2, adj_matrix) << endl;
    cout << "by floyd-warshall algorithm. ans:3, return:"<< floyd_warshall(0, 3, adj_matrix) << endl;
    cout << "by floyd-warshall algorithm. ans:8, return:"<< floyd_warshall(2, 4, adj_matrix) << endl;

}