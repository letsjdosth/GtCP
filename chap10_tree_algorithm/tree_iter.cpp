#include <iostream>
#include <vector>


using namespace std;

class Adj_tree{
    private:
        vector<vector<int>> adj_tree;
    
        //음..이함수는 참고용입니다... (깊이우선탐색 바닐라 버전)
        void dfs(int now_node, int prior_node){ //iteration
            //node s 처리
            cout << "now at: " << now_node << endl;

            for(auto u: adj_tree[now_node]){
                if(u == prior_node) continue;
                dfs(u, now_node);
            }
        }

    public:
        Adj_tree(vector<vector<int>> adj_vec){
            adj_tree = adj_vec;
        }

        //for diameter algorithm 1
        int to_leaf(int now_node, int subtree_root_node){
            //subtree_root_node는 subgraph의 root를 말함. 따라서 바로 부모 노드를 넣어주어야 함 (이거 개선할 수 있을지?)
            //트리 클래스에 멤버변수로 root를 받아놓자<-방법1
            //개선후 private로 보낼 것
                if(adj_tree[now_node].size()==1 && adj_tree[now_node][0]==subtree_root_node){
                    return 0;
                }

                int to_leaf_count = 0;
                for(auto u: adj_tree[now_node]){
                    if(u == subtree_root_node) continue;
                    int recursive_count = to_leaf(u, now_node);
                    if(recursive_count+1 > to_leaf_count) to_leaf_count = recursive_count+1;
                }
                return to_leaf_count;
        }

        //for diameter algorithm 1
        int max_length(int top_node){
            //마찬가지로 미리 그래프 구조를 알고 top_node를 제대로 넣지 않으면 (방향때문에)엉망으로 동작함. 개선방안?
            int length = 0;
            for(auto u: adj_tree[top_node]){
                for(auto v: adj_tree[top_node]){
                    if(u==v) continue;
                    int candidate = to_leaf(u, top_node) + to_leaf(v, top_node) + 2;
                    if(candidate>length) length=candidate;
                }
            }
            return length;
        }

        //for diameter algorithm 2
        pair<int,int> farthest_node(int now_node, int prior_node){
            //pair<int deep_count, int deep_node>
            pair<int,int> deep;
            if(adj_tree[now_node].size()==1 && adj_tree[now_node][0]==prior_node){
                deep.first = 0;
                deep.second = now_node;
                return deep;
            }
            
            for(auto u: adj_tree[now_node]){
                if(u == prior_node) continue;
                pair<int, int> recursive = farthest_node(u, now_node);
                if(recursive.first + 1 > deep.first) {
                    deep.first = recursive.first + 1;
                    deep.second = recursive.second;
                }
            }
            return deep;
        }

        //for diameter algorithm 2
        int max_length_2(int start_node = 0){
            //사실 start_node는 아무쓸데없어요 아무데서나시작해도 다같게나옴
            pair<int,int> first_step = farthest_node(start_node ,-1);
            pair<int,int> second_step = farthest_node(first_step.second, -1);
            return second_step.first;
        }

};


int main(){
    //example tree
    //      0
    // 1    2    3
    //4 5        6
    //  7
    vector<vector<int>> ex1_tree_adj_list(8);
    ex1_tree_adj_list[0] = {1,2,3};
    ex1_tree_adj_list[1] = {0,4,5};
    ex1_tree_adj_list[2] = {0};
    ex1_tree_adj_list[3] = {0,6};
    ex1_tree_adj_list[4] = {1};
    ex1_tree_adj_list[5] = {1,7};
    ex1_tree_adj_list[6] = {3};
    ex1_tree_adj_list[7] = {5};

    Adj_tree ex1_tree(ex1_tree_adj_list);
    cout << "<algorithm 1 test>" << endl;
    cout << "(submethod)to_leaf: " << ex1_tree.to_leaf(0,-1) << "(true:3)" << endl;
    cout << "(submethod)to_leaf: " << ex1_tree.to_leaf(1,0) << "(true:2)" << endl;
    cout << "(submethod)to_leaf: " << ex1_tree.to_leaf(3,0) << "(true:1)" << endl;
    cout << "max_length: " << ex1_tree.max_length(0) << "(max_length: 5)" << endl;

    cout << "<algorithm 2 test>" << endl;
    pair<int,int> farthest_test_result = ex1_tree.farthest_node(7, -1);
    cout << "(submethod)farthest_node: length " << farthest_test_result.first << " at node " << farthest_test_result.second << " (true: length 5 at node 6)" << endl;
    cout << "max_length: " << ex1_tree.max_length_2(0) << " (true: 5)" << endl;;

}