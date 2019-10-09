#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//strongly_conn_kosaraju.cpp에서 복붙해옴(ㅋㅋ)
class Kosaraju{
    private:
        vector<vector<int>> adj_graph;
        vector<vector<int>> reversed_adj_graph;
        vector<pair<int,int>> first_start_end; 

        int process_count;
        stack<int> stack_second_iter;
        vector<bool> second_processed;

        vector<vector<int>> strongly_conn_component;

        void print_vector(vector<int> input_vector){
            for(int u : input_vector){
                cout << u << " ";
            }
            cout << " ";
        }

        void print_graph(vector<vector<int>> input_graph){
            for(int i=0; i<input_graph.size(); i++){
                cout << i << ": ";
                for(int u : input_graph[i]){
                    cout << u << " ";
                }
                cout << "\n";
            }
        }

        void make_reverse_graph(){
            reversed_adj_graph.resize(adj_graph.size());
            for(int ortho_node=0; ortho_node<adj_graph.size(); ortho_node++){
                for(int u : adj_graph[ortho_node]){
                    reversed_adj_graph[u].push_back(ortho_node);
                }
            }
        }

        void first_dfs(int now_node, int prior_node){ //iteration
            //now_node 처리
            process_count++;
            first_start_end[now_node].first = process_count;
            stack_second_iter.push(now_node);

            for(auto u: adj_graph[now_node]){
                if(u == prior_node) continue;
                if(first_start_end[u].first!=-1) continue; 
                first_dfs(u, now_node);
            }

            process_count++;
            first_start_end[now_node].second = process_count;
            stack_second_iter.push(now_node);
        }

        void first_dfs_executor(){
            first_start_end.resize(adj_graph.size(), {-1,-1}); //처리안된노드 표현: -1
            process_count = 0;
            for(int start_node=0; start_node<adj_graph.size(); start_node++){
                if(first_start_end[start_node].first==-1)
                    first_dfs(start_node, -1);
            }
        }

        
        void second_dfs(int now_node, int prior_node, vector<int>& stage_conn_comp){
            second_processed[now_node] = true;
            stage_conn_comp.push_back(now_node);

            for(auto u: reversed_adj_graph[now_node]){
                if(u == prior_node) continue;
                if(second_processed[u]==true) continue; 
                second_dfs(u, now_node, stage_conn_comp);
            }
        }
        
        void second_dfs_executor(){
            second_processed.resize(reversed_adj_graph.size(), 0);
            int next;
            while(!stack_second_iter.empty()){
                next = stack_second_iter.top();
                stack_second_iter.pop();
                if(second_processed[next]) continue;
                else{
                    vector<int> stage_comp;
                    second_dfs(next, -1, stage_comp);
                    strongly_conn_component.push_back(stage_comp);
                }
            }
        }


    public:
        Kosaraju(vector<vector<int>> input_graph){
            adj_graph = input_graph;
            make_reverse_graph();
            first_dfs_executor();
            second_dfs_executor();
        }

        void print_strongly_conn_component(){
            cout << "Find Strongly Connected Components: by Kosaraju's algorithm\n";
            cout << "cmp: element(node index)\n";
            print_graph(strongly_conn_component);
            cout << endl;
        }

        vector<vector<int>> get_strongly_conn_component(){
            return strongly_conn_component;
        }

};

class Base_Eulerian_path{ 
    // directed/undirected graph에 따라 Euler circuit/path 판단기준이 다르므로
    // 공통으로쓰이는함수만 이 클래스에 두고
    // 상속받아 쓰자

    protected:
        vector<vector<int>> adj_graph;
        vector<pair<int,int>> in_out_degree; //<in_degree, out_degree>

        void make_in_out_degree(){
            in_out_degree.resize(adj_graph.size(),{0,0});
            for(int node=0; node<adj_graph.size(); node++){
                in_out_degree[node].second = adj_graph[node].size();
                for(int u: adj_graph[node]){
                    in_out_degree[u].first++;
                }
            }
        }

        bool is_one_comp(){
            Kosaraju comp_test(adj_graph);
            vector<vector<int>> graph_comp_vec;
            graph_comp_vec = comp_test.get_strongly_conn_component();
            if(graph_comp_vec.size()==1) return true;
            else return false;
        }

        void print_vector(vector<int> input_vector){
            //디버그용
            for(int u : input_vector){
                cout << u << " ";
            }
            cout << " ";
        }

    public:
        //안쓰더라도 상속을 위해 arg 없는 빈 생성자가 필요한가봄(나중에 c++문법 확인)
        Base_Eulerian_path(){
            adj_graph = {};
        }

        Base_Eulerian_path(vector<vector<int>> input_graph){
            adj_graph = input_graph;
            make_in_out_degree();
        }
};


class Eulerian_path_undirected : public Base_Eulerian_path {
    private:
        vector<int> get_odd_degree_nodes() {
            //for undirected graph
            vector<int> odd_degree_nodes_list;
            for(int i=0; i<in_out_degree.size(); i++){
                if(in_out_degree[i].first%2==1)
                    odd_degree_nodes_list.push_back(i);
            }
            return odd_degree_nodes_list;
        }

        bool is_all_degree_even(){
            //for undirected graph
            for(pair<int,int> in_out_pair : in_out_degree){
                if(in_out_pair.first % 2 ==1){
                    return false;
                }
                if(in_out_pair.second % 2 == 1){
                    return false;
                }
            }
            return true;
        }

        int find_start(vector<vector<int>>& adj_edge_processed_input, vector<bool>& adj_node_processed_input){
            //find_euler_circuit_seq_hierholzer 보조함수
            for(int i=0; i<adj_graph.size();i++){
                if(!adj_node_processed_input[i]) continue;
                for(int edge=0; edge<adj_graph[i].size(); edge++){
                    if(adj_edge_processed_input[i][edge] == 0){
                       return i;
                    }
                }
            }
            return -1; //모두 처리되어서 잡을 start 포인트가 없다면
        }
    
    public:
        //생성자
        Eulerian_path_undirected(vector<vector<int>> input_graph) : Base_Eulerian_path(input_graph){
        }

        bool is_euler_circuit(){
            //for undirected graph
            if(!is_one_comp()) return false;
            
            if(is_all_degree_even()) return true;
            else return false;
        }

        bool is_euler_path(){
            //for undirected graph
            if(!is_one_comp()) return false;
            if(is_euler_circuit()) return true;
            else {
                vector<int> test_euler_path_vec = get_odd_degree_nodes();
                if(test_euler_path_vec.size()==2) return true;
                else return false;
            }
        }

        vector<vector<int>> find_euler_circuit_seq_hierholzer(){
            //euler circuit 있을때만 제대로 동작
            //edge status & node status 초기화
            vector<vector<int>> adj_edge_processed; //bool로 하면 더 효율적이겠지만..
            vector<bool> adj_node_processed(adj_graph.size(), false);
            adj_edge_processed = adj_graph;
            for(int i=0;i<adj_edge_processed.size(); i++){
                for(int j=0; j<adj_edge_processed[i].size();j++){
                    adj_edge_processed[i][j]=0;
                }
            }

            vector<vector<int>> circuit_component;
            int start_node=0;
            //투어
            while(true){
                // cout << "stage "<< iter << " start" << start_node << " "; //for debug
                if (start_node==-1) break;

                vector<int> stage_circuit;
                int now_node = start_node;
                while(now_node!=start_node || stage_circuit.size()==0){
                    adj_node_processed[now_node]=true;
                    stage_circuit.push_back(now_node);
                    for(int i=0; i<adj_edge_processed[now_node].size(); i++){
                        if(adj_edge_processed[now_node][i]==0){
                            int next_node = adj_graph[now_node][i];
                            
                            adj_edge_processed[now_node][i]=1;
                            for(int k=0; k<adj_edge_processed[next_node].size(); k++){
                                if(adj_graph[next_node][k]==now_node) adj_edge_processed[next_node][k]=1;
                            }
                            now_node=next_node;
                            break;
                        }
                    }
                }
                stage_circuit.push_back(start_node);
                // cout << " push: "; print_vector(stage_circuit); cout << "\n"; //for debug
                circuit_component.push_back(stage_circuit);
                stage_circuit.clear();
                start_node = find_start(adj_edge_processed, adj_node_processed);
            }
            return circuit_component;
        }
};

class Eulerian_path_directed : public Base_Eulerian_path {
    private:
        bool is_same_inout_all_nodes(){
            //for directed graph
            for(pair<int,int> in_out_pair : in_out_degree){
                if(in_out_pair.first != in_out_pair.second) return false;
            }
            return true;
        }

        vector<int> get_diff_inout_degree_node(){
            vector<int> diff_degree_nodes_list;
            for(int i=0; i<adj_graph.size(); i++){
                if(in_out_degree[i].first!=in_out_degree[i].second){
                    diff_degree_nodes_list.push_back(i);
                }
            }
            return diff_degree_nodes_list;
        }

    public: 
        //생성자
        Eulerian_path_directed(vector<vector<int>> input_graph) : Base_Eulerian_path(input_graph){
        }
        
        bool is_euler_circuit(){
            //for directed graph
            if(!is_one_comp()) return false;
            
            if(is_same_inout_all_nodes()) return true;
            else return false;
        }

        bool is_euler_path(){
            //for directed graph
            if(!is_one_comp()) return false;
            if(is_euler_circuit()) return true;
            else {
                vector<int> test_euler_path_vec = get_diff_inout_degree_node();
                if(test_euler_path_vec.size()!=2) return false;
                else{
                    int verify_1_or_minus1=0;
                    verify_1_or_minus1 += in_out_degree[test_euler_path_vec[0]].first - in_out_degree[test_euler_path_vec[0]].second;
                    if(verify_1_or_minus1==1 || verify_1_or_minus1==-1){
                        verify_1_or_minus1 += in_out_degree[test_euler_path_vec[1]].first - in_out_degree[test_euler_path_vec[1]].second;
                        if(verify_1_or_minus1==0) return true;
                    }
                    return false;
                }
            }
        }
};



int main(){
    // 0 - 1 \ 
    // |   |  2
    // 3 - 4 /
    vector<vector<int>> ex1_undirect_graph(5);
    ex1_undirect_graph[0] = {1,3};
    ex1_undirect_graph[1] = {0,2,4};
    ex1_undirect_graph[2] = {1,4};
    ex1_undirect_graph[3] = {0,4};
    ex1_undirect_graph[4] = {1,2,3};

    Eulerian_path_undirected ex1 (ex1_undirect_graph);
    cout << "<ex1> exist euler circuit? " << ex1.is_euler_circuit() << " (true:0)\n";
    cout << "<ex1> exist euler path? " << ex1.is_euler_path() << " (true:1)\n";
    

    // 0 - 1 \ 
    // | / |  2
    // 3   4 /
    vector<vector<int>> ex2_undirect_graph(5);
    ex2_undirect_graph[0] = {1,3};
    ex2_undirect_graph[1] = {0,2,3,4};
    ex2_undirect_graph[2] = {1,4};
    ex2_undirect_graph[3] = {0,1};
    ex2_undirect_graph[4] = {1,2};

    Eulerian_path_undirected ex2 (ex2_undirect_graph);
    cout << "<ex2> exist euler circuit? " << ex2.is_euler_circuit() << " (true:1)\n";
    cout << "<ex2> exist euler path? " << ex2.is_euler_path() << " (true:1)\n";
    cout << "<ex2> finding circuit?";
    vector<vector<int>> ex2_hierholzer = ex2.find_euler_circuit_seq_hierholzer();
    for(vector<int> u : ex2_hierholzer){
        cout << " [";
        for(int v: u){
            cout << v << " ";
        }
        cout << "] ";
    }
    cout << "\n";

    // 0 -> 1 -> 2
    // ^    v   /
    // 3 <- 4  <
    vector<vector<int>> ex3_direct_graph(5);
    ex3_direct_graph[0] = {1};
    ex3_direct_graph[1] = {2,4};
    ex3_direct_graph[2] = {4};
    ex3_direct_graph[3] = {0};
    ex3_direct_graph[4] = {3};

    Eulerian_path_directed ex3 (ex3_direct_graph);
    cout << "<ex3> exist euler circuit? " << ex3.is_euler_circuit() << " (true:0)\n";
    cout << "<ex3> exist euler path? " << ex3.is_euler_path() << " (true:1)\n";

    //     0
    //  /  |
    // 1 - 2 - 3
    // | \ |   |
    // 4 - 5 - 6
    vector<vector<int>> ex4_undirect_graph(7);
    ex4_undirect_graph[0] = {1,2};
    ex4_undirect_graph[1] = {0,2,4,5};
    ex4_undirect_graph[2] = {0,1,3,5};
    ex4_undirect_graph[3] = {2,6};
    ex4_undirect_graph[4] = {1,5};
    ex4_undirect_graph[5] = {1,2,4,6};
    ex4_undirect_graph[6] = {3,5};

    Eulerian_path_undirected ex4 (ex4_undirect_graph);
    cout << "<ex4> exist euler circuit? " << ex4.is_euler_circuit() << " (true:1)\n";
    cout << "<ex4> exist euler path? " << ex4.is_euler_path() << " (true:1)\n";
    cout << "<ex4> finding circuit?";
    vector<vector<int>> ex4_hierholzer = ex4.find_euler_circuit_seq_hierholzer();
    for(vector<int> u : ex4_hierholzer){
        cout << " [";
        for(int v: u){
            cout << v << " ";
        }
        cout << "] ";
    }
    cout << "\n";
}