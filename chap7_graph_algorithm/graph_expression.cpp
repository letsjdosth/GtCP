#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main(){
    //주의: 실제 사용에서는 index를 -1씩 밀 것 (0번째를 비우지 말고, 1번째 node에 해당하는 식으로 쓸 것)

    //1. adjacency list expression
    //ex1
    //                node index [  1,     2,   3,   4, ... ]
    //able to go from above node [[2], [3,4], [4], [1], ... ]
    vector<vector<int>> adj(5);
    adj[1].push_back(2);
    adj[2].push_back(3); adj[2].push_back(4);
    adj[3].push_back(4);
    adj[4].push_back(1);
    //ex2
    //weighted graph
    //                                node index [1      , 2            ,3,     ,4]
    // <able to go from above note, each weight> [[(2,5)], [(3,7),(4,6)],[(4,5)],[(1,2)]]
    vector<vector<pair<int,int>>> weighted_adj(5);
    weighted_adj[1].push_back[{2,5}];
    weighted_adj[2].push_back[{3,7}]; weighted_adj[2].push_back[{4,6}];
    weighted_adj[3].push_back[{4,5}];
    weighted_adj[4].push_back[{1,2}];

    //2. adjacency matrix expression
    //ex1
    //row index->col index 의 weight를 줌.(0이면 edge가 없는 것.)
    vector<vector<int>> adj_matrix(4,{0,0,0,0});
    adj_matrix[1-1][2-1]=1;
    adj_matrix[2-1][3-1]=1; adj_matrix[2-1][4-1]=1;
    adj_matrix[3-1][4-1]=1;
    adj_matrix[4-1][1-1]=1;
    //ex2
    vector<vector<int>> weighted_adj_matrix(4,{0,0,0,0});
    weighted_adj_matrix[1-1][2-1]=5;
    weighted_adj_matrix[2-1][3-1]=7; weighted_adj_matrix[2-1][4-1]=6;
    weighted_adj_matrix[3-1][4-1]=5;
    weighted_adj_matrix[4-1][1-1]=2;

    //3. edge list expression
    //그냥 edge를 나열함
    //ex1 {end node, end node}
    vector<pair<int,int>> edges;
    edges.push_back({1,2});
    edges.push_back({2,3}); edges.push_back({2,4});
    edges.push_back({3,4});
    edges.push_back({4,1});
    //ex2 {end node, end node, weight}
    vector<tuple<int,int,int>> weighted_edges;
    weighted_edges.push_back({1,2,5});
    weighted_edges.push_back({2,3,7}); weighted_edges.push_back({2,4,6});
    weighted_edges.push_back({3,4,5});
    weighted_edges.push_back({4,1,2});
}