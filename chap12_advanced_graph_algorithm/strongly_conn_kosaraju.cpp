#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Kosaraju{
    private:
        vector<vector<int>> adj_graph;
        vector<vector<int>> reversed_adj_graph;
        vector<pair<int,int>> first_start_end; 
        //사실 이 정보는 좀 redundant함 (어차피 2번째 dfs를 위해 스택에 노드를 넣어놓기때문에.. 카운팅한걸 굳이 붙여놓을필요는 없음)
        //하지만 첫 dfs 코드에서 이미 처리한노드인지 확인할때 이 pair를 들여다보기때문에..일단 냅두겠음..
        //(나중에 vector<bool>로, 이미 처리된 노드에 대해 플래그역할을 하도록 대체해버리면 더 효율적일듯)

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
            // print_graph(reversed_adj_graph); //for debug
        }

        void first_dfs(int now_node, int prior_node){ //iteration
            //now_node 처리
            process_count++;
            first_start_end[now_node].first = process_count;
            stack_second_iter.push(now_node);
            cout << "(first_dfs) now: " << now_node << " with process count " << process_count << "\n"; //for debug

            for(auto u: adj_graph[now_node]){
                if(u == prior_node) continue;
                if(first_start_end[u].first!=-1) continue; 
                //이미 처리된노드는 가지말자(이게없으면 cycle이 있으면 무한히돌고 한노드로가는 여러경로가 있으면 두번 돌기때문에..)
                first_dfs(u, now_node);
            }

            process_count++;
            first_start_end[now_node].second = process_count;
            stack_second_iter.push(now_node);
            cout << "(first_dfs) now: " << now_node << " with process count " << process_count << "\n"; //for debug
        }

        void first_dfs_executor(){
            first_start_end.resize(adj_graph.size(), {-1,-1}); //처리안된노드 표현: -1
            process_count = 0;
            for(int start_node=0; start_node<adj_graph.size(); start_node++){
                //이 for문: dfs가 한 경로 있는쪽만 돌고 끝나기때문에.. 못간 노드가 있을수도있으므로 한번은 다 시작점으로 돌려봐야한다
                if(first_start_end[start_node].first==-1) //이전 노드를 시작점으로했을때 dfs로 돌아서 이미처리된노드면 패스하자
                    first_dfs(start_node, -1);
            }
            cout << "(first_dfs) final count: " << process_count << " (true:14)\n";  //for debug
        }

        
        void second_dfs(int now_node, int prior_node, vector<int>& stage_conn_comp){ //iteration
            //now_node 처리
            second_processed[now_node] = true;
            stage_conn_comp.push_back(now_node);
            cout << "(second_dfs) now at node:" << now_node << "/processed comp?  "; print_vector(stage_conn_comp); cout << "\n"; //for debug

            for(auto u: reversed_adj_graph[now_node]){
                if(u == prior_node) continue;
                if(second_processed[u]==true) continue; 
                second_dfs(u, now_node, stage_conn_comp);
                // stage_conn_comp = second_dfs(u, now_node, stage_conn_comp);
            }
            // return stage_conn_comp;
            
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
                    cout << "push component: "; print_vector(stage_comp); cout <<"\n"; //for debug
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

};

int main(){
//     0 <-> 1 <- 2  -> 6
//     v     v    ^   / 
//     3 <-  4 <- 5  <
    vector<vector<int>> ex_graph(7);
    ex_graph[0] = {1,3};
    ex_graph[1] = {0,4};
    ex_graph[2] = {1,6};
    ex_graph[3] = {};
    ex_graph[4] = {3};
    ex_graph[5] = {2,4};
    ex_graph[6] = {5};

    Kosaraju ex_algo(ex_graph);
    ex_algo.print_strongly_conn_component();

}
