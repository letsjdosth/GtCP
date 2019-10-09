#include <iostream>
#include <vector>

using namespace std;

class DepthFirst_search_tree{
    private:
        vector<vector<int>> adj_graph;
        vector<vector<int>> tree_edges;
        vector<vector<int>> back_edges;
        vector<int> level;
        int root;
        vector<int> cut_nodes;
        vector<vector<int>> cut_edges;

        int make_DF_adj_dfs(int now_node, int prior_node, vector<bool>& visited, int& cumul_level){
            //make_DF_adj_executor로 실행할것
            visited[now_node] = true;
            cumul_level++;
            level[now_node] = cumul_level;

            if(prior_node!=-1)
                tree_edges[prior_node].push_back(now_node);

            for(int u : adj_graph[now_node]){
                if(u == prior_node)
                    continue;
                if(visited[u]==true){
                    if(level[u]>level[now_node])
                        back_edges[u].push_back(now_node);
                    continue;
                }
                make_DF_adj_dfs(u, now_node, visited, cumul_level);
            }
        }

        void make_DF_adj_executor(){
            //tree_edges, back_edges, level 만들기
            tree_edges.resize(adj_graph.size(),{});
            back_edges.resize(adj_graph.size(),{});
            level.resize(adj_graph.size(),0);
            vector<bool> visited_node_cheak(adj_graph.size(), false);
            int level_idx=0;
            make_DF_adj_dfs(root, -1, visited_node_cheak, level_idx);
        }

        void print_graph(vector<vector<int>> input_graph){
            for(vector<int> u : input_graph){
                cout << "[";
                for(int v: u){
                    cout << v << ",";
                }
                cout << "], ";
            }
            cout << "\n";
        }

        void subtree_dfs(int now_node, vector<int>& subtree_result_vec){
            //get_subtree_nodes 보조
            for(int u : tree_edges[now_node]){
                if(level[u] <= level[now_node]) continue;
                
                subtree_result_vec.push_back(u);
                subtree_dfs(u, subtree_result_vec);
            }
        }

        vector<int> get_subtree_nodes(int subtree_root){
            vector<int> subtree_nodes;
            subtree_dfs(subtree_root, subtree_nodes);
            return subtree_nodes;
        }

        bool exist_subtree_has_back_edge_to_up(int subtree_root, int bench_node, bool include_root=false, bool include_bench=false){
            //subtree root: 검사대상노드 설정
            //      1. include_root=false : subtree_root를 제외한 subtree의 member node 검사
            //      2. include_root=true : subtree_root를 포함한 subtree의 member node 검사
            //bench_node: backedge 있는지 업는지 판단할 판단기준노드 설정
            //      1. include_bench=false : bench_node의 조상으로 가는 back_edge가 있으면 true
            //      2. include_bench=true : bench_node 혹은 bench_node의 조상으로 가능 back_edge가 있으면 true

            vector<int> subtree_of_node;
            subtree_of_node = get_subtree_nodes(subtree_root);
            if(include_root) subtree_of_node.push_back(subtree_root);
            bool exist_back_edge_to_up = false;
            for(int u : subtree_of_node){
                for(int v: back_edges[u]){
                    bool include_bench_flag;
                    if(include_bench==false) include_bench_flag = (level[v] < level[bench_node]);
                    else include_bench_flag = (level[v] <= level[bench_node]);

                    if(include_bench_flag) exist_back_edge_to_up = true;
                }
            }
            return exist_back_edge_to_up;
        }

        void find_articulation_point(){
            //cut_nodes 만들기
            for(int node=0; node<adj_graph.size(); node++){
                //root일 경우
                if(node==root){
                    if(tree_edges[node].size()>=2) cut_nodes.push_back(node);
                } else if(tree_edges[node].size()==0){ //끝점일 경우
                    continue;
                } else { //기타
                    bool exist_backedge_to_up = exist_subtree_has_back_edge_to_up(node, node);
                    if(!exist_backedge_to_up) cut_nodes.push_back(node);
                }
            }
        }

        void find_bridge(){
            //cut_edges 만들기
            for(int node=0; node<tree_edges.size(); node++){
                for(int edge_in_node=0; edge_in_node<tree_edges[node].size(); edge_in_node++){
                    int next_node = tree_edges[node][edge_in_node];
                    vector<int> next_node_root_subtree = get_subtree_nodes(next_node);
                    next_node_root_subtree.push_back(next_node);
                    bool exist_backedge_to_up = false;
                    for(int u : next_node_root_subtree){
                        exist_backedge_to_up |= exist_subtree_has_back_edge_to_up(u, node, true, true);
                    }
                    if(!exist_backedge_to_up) cut_edges.push_back({node, next_node});
                }
            }
        }

    
    public:
        DepthFirst_search_tree(vector<vector<int>> input_graph, int input_root){
            adj_graph = input_graph;
            root = input_root;
            make_DF_adj_executor();
            find_articulation_point();
            find_bridge();

            vector<int> temp = get_subtree_nodes(2);
            cout << "test: ";
            for(int u : temp){
                cout << u << " ";
            }
            cout << endl;
        }

        vector<vector<int>> get_tree_edges(){
            return tree_edges;
        }

        vector<vector<int>> get_back_edges(){
            return back_edges;
        }

        void print_tree_edges(){
            cout << "tree edges: ";
            print_graph(tree_edges);
        }

        void print_back_edges(){
            cout << "back edges: ";
            print_graph(back_edges);
        }

        void print_articulation_point(){
            cout << "cut- nodes: ";
            for(int u : cut_nodes)
                cout << u << ", ";
            cout << endl;
        }

        void print_bridge(){
            cout << "bridges   : ";
            print_graph(cut_edges);
        }

};

int main(){
//   /- 1 -\     /- 5
// 0    |   3 - 4   |
//   \- 2 -/     \- 6 - 7
    vector<vector<int>> ex_graph(8);
    ex_graph[0] = {1,2};
    ex_graph[1] = {0,2,3};
    ex_graph[2] = {0,1,3};
    ex_graph[3] = {1,2,4};
    ex_graph[4] = {3,5,6};
    ex_graph[5] = {4,6};
    ex_graph[6] = {4,5,7};
    ex_graph[7] = {6};

    DepthFirst_search_tree ex_dfst (ex_graph,4);
    
    ex_dfst.print_tree_edges();
    ex_dfst.print_back_edges();
    ex_dfst.print_articulation_point();
    ex_dfst.print_bridge();
}