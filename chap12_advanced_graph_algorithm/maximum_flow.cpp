#include <iostream>
#include <vector>
#include <tuple>
#include <set>

using namespace std;

class Maximum_flow_cal{
    private:
        vector<vector<pair<int,int>>> extended_pair_graph; //pair<다음노드, weight>
        int sink;
        int source;
        int max_flow;
        set<int> able_to_go_from_source;
        vector<vector<int>> minimum_cut;
        
        void make_extended_pair_graph(vector<vector<pair<int,int>>> input_adj_weighted_graph){
           extended_pair_graph = input_adj_weighted_graph;
           for(int node_idx=0; node_idx<input_adj_weighted_graph.size(); node_idx++){
                for(int edge_idx=0; edge_idx<input_adj_weighted_graph[node_idx].size(); edge_idx++){
                    int next_node = input_adj_weighted_graph[node_idx][edge_idx].first;
                    pair<int,int> new_pair_edge = {node_idx, 0};
                    extended_pair_graph[next_node].push_back(new_pair_edge);
                }
            }
        }
    
        void print_vector(vector<int> input_vec){
            for(int u : input_vec){
                cout << u << " ";
            }
            cout << "\n";
        }
        
        void print_graph(vector<vector<pair<int,int>>> input_pair_graph){
            for(vector<pair<int,int>> u : input_pair_graph){
                cout << "[";
                for(pair<int,int> v : u){
                    int a = v.first;
                    int b = v.second;
                    cout << "<" << a << "," << b << ">,";
                }
                cout << "], ";
            }
            cout << "\n";
        }


        bool find_path_by_dfs(int now_node, int prior_node, vector<int>& input_stage_path, int& stage_min, vector<bool>& visited){ //iteration
            //now_node 처리
            // cout << "now: " << now_node << " "; //for debug
            if(now_node==sink){
                input_stage_path.push_back(sink);
                visited[sink] = true;
                // cout << "\n"; //for debug
                return true;
            }
            visited[now_node]=true;
            for(auto u: extended_pair_graph[now_node]){
                int node, weight;
                tie(node, weight) = u;
                
                if(node == prior_node) continue;
                if(visited[node]) continue;
                if(weight==0) continue;

                if(find_path_by_dfs(node, now_node, input_stage_path, stage_min, visited)){
                    input_stage_path.push_back(now_node);
                    if(stage_min>weight) stage_min=weight;
                    return true;
                }
            }
            return false;
        }
        

        bool find_path(vector<int>& stage_path, int& stage_min){
            vector<bool> visited(extended_pair_graph.size(),0);
            bool exist = find_path_by_dfs(source, -1, stage_path, stage_min, visited);
            return exist;
        }

        
        int stage_executor(){
            vector<int> stage_path;
            int stage_min = ((unsigned int)(~0))>>1; //큰수
            find_path(stage_path, stage_min);
            
            cout << "stage path: ";//for debug
            print_vector(stage_path); //for debug
            cout << "stage min: " << stage_min << endl; //for debug
            
            // adjust weight
            while(stage_path.size()>1){
                int from = stage_path.back(); stage_path.pop_back();
                int to = stage_path.back();
                //정방향 업데이트                
                for(int edge_idx=0; edge_idx<extended_pair_graph[from].size(); edge_idx++){
                    int node, weight;
                    tie(node, weight) = extended_pair_graph[from][edge_idx];
                    if(node == to){
                        weight-=stage_min;
                        pair<int,int> updated_edge = {node, weight};
                        swap(extended_pair_graph[from][edge_idx], updated_edge);
                    }
                }
                //역방향 업데이트
                for(int edge_idx=0; edge_idx<extended_pair_graph[to].size(); edge_idx++){
                    int reverse_node, reverse_weight;
                    tie(reverse_node, reverse_weight) = extended_pair_graph[to][edge_idx];
                    if(reverse_node == from){
                        reverse_weight+=stage_min;
                        pair<int,int> updated_reverse_edge = {reverse_node, reverse_weight};
                        swap(extended_pair_graph[to][edge_idx], updated_reverse_edge);
                    }
                }
            }
            return stage_min;
        }

        void ford_fulkerson_executor(){
            int flow = 0;
            while(true){
                vector<int> dummy_vec; int dummy_int=((unsigned int)(~0))>>1;
                if(find_path(dummy_vec, dummy_int)){
                    flow += stage_executor();
                    print_graph(extended_pair_graph);
                } else{
                    break;
                }
            }
            max_flow = flow;
        }


        void able_to_go_from(int from, set<int>& result_set, vector<bool>& visited){
            visited[from] = true;
            for(pair<int,int> next : extended_pair_graph[from]){
                if(next.second!=0 && !visited[next.first]){
                    result_set.insert(next.first);
                    able_to_go_from(next.first, result_set, visited);
                }
            }
        }

        void make_able_to_go_from_source(){
            set<int> able_to_go;
            vector<bool> visited(extended_pair_graph.size(),false);
            able_to_go.insert(source);
            able_to_go_from(source, able_to_go, visited);
            //for debug
            // for(int u : able_to_go){
            //     cout << u << " ";
            // }
            able_to_go_from_source = able_to_go;
        }

        void make_minimum_cut(){
            vector<vector<int>> minimum_cut_vec;
            for(int node : able_to_go_from_source){
                for(pair<int,int> edge : extended_pair_graph[node]){
                    int candid = edge.first;
                    bool in_flag = false;
                    for(int u : able_to_go_from_source){
                        if(candid==u) in_flag=true;
                    }
                    if(in_flag==false){
                        vector<int> cut = {node, candid};
                        minimum_cut_vec.push_back(cut);
                    }
                }
            }
            minimum_cut= minimum_cut_vec;
        }

    public:
        Maximum_flow_cal(vector<vector<pair<int,int>>> adj_weighted_graph, int input_source, int input_sink){
            source = input_source;
            sink = input_sink;
            make_extended_pair_graph(adj_weighted_graph);
            ford_fulkerson_executor();
            make_able_to_go_from_source();
            make_minimum_cut();
        }

        int get_max_flow(){
            //ford_fulkerson_executor 실행 후 사용
            return max_flow;
        }

        vector<vector<int>> get_minimum_cut(){
            return minimum_cut;
        }

        void print_minimum_cut(){
            for(vector<int> u : minimum_cut){
                cout << "["<<u[0] << "," <<u[1] << "], ";
            }
            cout << endl;
        }
};

int main(){
//        1 -(6)-> 2
//  (5)/^ ^        |  \v(5)
//  0    (3)      (8)    5
//  (4)\v |        v  /^(2)
//        3 -(1)-> 4
    vector<vector<pair<int,int>>> ex_graph(6);
    ex_graph[0] = {{1,5},{3,4}};
    ex_graph[1] = {{2,6}};
    ex_graph[2] = {{4,8},{5,5}};
    ex_graph[3] = {{1,3},{4,1}};
    ex_graph[4] = {{5,2}};
    ex_graph[5] = {};
    Maximum_flow_cal ex_graph_inst(ex_graph, 0, 5);
    cout << "max flow: " << ex_graph_inst.get_max_flow() << " (true:7)\n";
    cout << "min cut : ";
    ex_graph_inst.print_minimum_cut();

}