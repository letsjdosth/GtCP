#include <iostream>
#include <vector>
#include <tuple>
#include <set>

#include <limits>

using namespace std;

//O(mn) : n round, m number of edges
int bellman_ford(int from, int to, vector<tuple<int,int,int>> graph_edge_list){
    //graph의 node 수 세기 (더 좋은방법?)
    set<int> node_vector;
    for(tuple<int,int,int> edge : graph_edge_list){
        node_vector.insert(std::get<0>(edge));
        node_vector.insert(std::get<1>(edge));
    }
    int num_nodes = node_vector.size();

    //distance vector
    int INF = std::numeric_limits<int>::max()-1;
    vector<int> distance(num_nodes);
    vector<int> last_round_distance(num_nodes);
    for(int i=0; i<num_nodes; i++){
        distance[i] = INF;
        last_round_distance[i] = INF;
    }
    
    //start
    distance[from] = 0;
    //calculate distance from start node
    for(int i=0; i < num_nodes-1; i++){
        for(tuple<int,int,int> edge : graph_edge_list){
            int a,b,weight;
            tie(a,b,weight) = edge;
            distance[b] = min(distance[b], distance[a]+weight);
        }
        if(distance == last_round_distance){  //여기 찝찝함에 대해: 아래 벡터에 대한 테스트 참고. 각자리 값이 같나 검사한다.
            cout << "algorithm is ended early for efficienty at "<< i+1 << "-th round." << endl;
            break;
        } 
        last_round_distance = distance; //마찬가지로 여기의 찝찝함에 대해: 아래 참고. 값을 복사한다.(참조를 바꾸는게 아니라)
        
    }
    return distance[to];
}


int main(){
    //example(graph of edge list expression)
    // 0 - (2) -   1 \ 
    // |\          |  \-(5)-\ 
    //(3) \-(7)-\ (3)        4
    // |          \|  /- (2)-/
    // 2 - (1) -   3 /
    vector<tuple<int,int,int>> edges; //{node, node, weight}
    edges.push_back({0,1,2}); edges.push_back({0,2,3}); edges.push_back({0,3,7});
    edges.push_back({1,3,3}); edges.push_back({1,4,5});
    edges.push_back({2,3,1});
    edges.push_back({3,4,2});

    cout << "by Bellman-Ford algorithm. ans:6, return:"<< bellman_ford(0, 4, edges) << endl;
    cout << "by Bellman-Ford algorithm. ans:4, return:"<< bellman_ford(0, 3, edges) << endl;

    //참고: 벡터 실험
    vector<int> test = {1,2,3,4};
    vector<int> test2 = test; 
    //아래 결과를 보면, 위처럼 할당하는것이, test2의 참조를 test1과 같게 바꾸는게아니라 다른 메모리공간에 값을 걍 복사하나봄
    test[3]=5;
    bool testbool = (test== test2);
    cout << testbool << " " <<test[3] << " " << test2[3] << endl; // 0 5 4 <-test2는 걍 4로 남아있음
}