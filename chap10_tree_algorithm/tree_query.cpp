#include <vector>
#include <iostream>

using namespace std;


class Adj_tree{
    private:
        int root_node;
        vector<vector<int>> adj_tree;
        
        vector<int> parents;
        vector<vector<int>> ancestor_pre_cal; //2^(k-1)번째 조상 벡터

        vector<int> tree_traversal_vector;
        vector<int> subtree_size;

        vector<int> normal_depth;
        vector<pair<int,int>> euler_depth;
        
        
        // for constructor //

        void make_parents_vector(int now_node, int prior_node){
            parents.resize(adj_tree.size());
            parents[now_node] = prior_node;
            // cout << "parents[" << now_node << "]=" << prior_node << endl; //for debug
            for(auto u: adj_tree[now_node]){
                if(u == prior_node) continue;
                make_parents_vector(u, now_node);
            }
        }

        void make_ancestor_pre_calculation(){
            //(x,1)
            ancestor_pre_cal.push_back(parents);
            vector<int> last_stage_ancestor = parents;
            vector<int> this_stage_ancestor(last_stage_ancestor.size());
            
            //(x,k)
            int iter = 2;
            while(iter<adj_tree.size()){
                for(int i=0; i<this_stage_ancestor.size(); i++){
                    if(last_stage_ancestor[i] != -1){
                        this_stage_ancestor[i]=parents[last_stage_ancestor[i]];
                    } else {
                        this_stage_ancestor[i] = root_node;
                    }
                }

                if(!(iter & (iter-1))) {
                    ancestor_pre_cal.push_back(this_stage_ancestor);
                    // cout << "added:" << iter << " stage\n"; //for debug
                    
                    bool not_allzero_flag=true;
                    for(int u : this_stage_ancestor){
                        not_allzero_flag &= u;
                    }
                    if(!not_allzero_flag) {
                        // cout<< "break at " << iter << " stage\n"; //for debug
                        break;
                    }
                }
                last_stage_ancestor = this_stage_ancestor;
                iter++;
                
            }
        }

        //서브트리: tree traversal array(트리순회배열) 만들기위한 dfs
        void make_traversal_vector_with_dfs(int now_node, int prior_node){
            tree_traversal_vector.push_back(now_node);
            for(auto u: adj_tree[now_node]){
                if(u == prior_node) continue;
                    make_traversal_vector_with_dfs(u, now_node);
            }
        }

        int subtree_size_cal(int now_node){
            if(adj_tree[now_node].size()==1) return 1;
            else{
                int sum = 1;
                for(int u : adj_tree[now_node]){
                    if(u==parents[now_node]) continue;
                    sum += subtree_size_cal(u);
                }
                return sum;
            }
        }

        void make_subtree_size_vec(){
            subtree_size.resize(adj_tree.size());
            for(int i=0; i<adj_tree.size(); i++){
                subtree_size[i] = subtree_size_cal(i);
            }
        }

        void make_depth_vec_with_dfs(int now_node, int prior_node, int prior_depth){
            int depth = ++prior_depth;
            pair<int,int> stage_pair = {now_node, depth};
            euler_depth.push_back(stage_pair);
            normal_depth[now_node] = depth;

            for(auto u: adj_tree[now_node]){
                if(u == prior_node) continue;
                    make_depth_vec_with_dfs(u, now_node, depth);
                    euler_depth.push_back(stage_pair); //오일러 투어를 위해서는 다시 올라왔을때 또 push해줘야한다.
            }
        }

        void make_2depth_vec(){
            normal_depth.resize(adj_tree.size());
            make_depth_vec_with_dfs(root_node, -1, 0);
        }

    public:
        Adj_tree(vector<vector<int>> adj_vec, int root_node_idx){
            adj_tree = adj_vec;
            root_node = root_node_idx;
            
            make_parents_vector(root_node, -1);
            parents[root_node]=root_node;
            make_ancestor_pre_calculation();
            make_traversal_vector_with_dfs(root_node, -1);
            make_subtree_size_vec();
            make_2depth_vec();
        }
        
        //10.2.1 k번째 조상 찾기
        int find_kth_ancestor(int now_node, int k){
            //2k가지고 만들것
            // cout << "now k : " << k << endl; //for debug
            int able_max_k = (1 << (ancestor_pre_cal.size() - 1));
          
            if(k==0) return now_node;
            if(k==1){
                return ancestor_pre_cal[0][now_node];
            }
            if(k%2!=0)
                return find_kth_ancestor(find_kth_ancestor(now_node, 1), k-1);
            else if(k > able_max_k) 
                return find_kth_ancestor(find_kth_ancestor(now_node, k/2), k/2);
            else{
                int stage_k = k;
                int exponent2 = 0;
                while(stage_k != 0){ //지수 편하게 구하는법? (사실 exponent2=sqrt(k)가 필요했음) //이 와일문 나중에 또 쓸일있으면 별도 함수로 떼자
                    stage_k -= stage_k & -stage_k; //2진수표현에서 맨 오른쪽의 1이 나오는 자리수의 10진수값을 준다.
                    exponent2++;
                }
                return find_kth_ancestor(ancestor_pre_cal[exponent2][now_node], k - (1<<exponent2));
            }
        }

        //10.2.2 subtree 출력(합은 안했음..)
        void print_subtree_of_node(int now_node){
            int size = subtree_size[now_node];
            cout << "subtree of node " << now_node << "? ";
            for(int i=0; i<size; i++){
                cout << tree_traversal_vector[now_node + i] << " ";
            }
            cout << "(size: " << size << ")" << endl;
        }


        //10.2.3 최소공통조상
        int lowest_common_ancestor_by_euler_tour(int node1, int node2){
            int first_pointer = -1;
            for(int i=0; i<euler_depth.size(); i++){
                if((euler_depth[i].first==node1) || (euler_depth[i].first==node2)){
                    first_pointer=i;
                    break;
                }
            }
            pair<int,int> min = {-1, adj_tree.size()+1};
            if(euler_depth[first_pointer].first==node1){
                for(int i=first_pointer+1; i<euler_depth.size(); i++){
                    if(euler_depth[i].second < min.second){
                        min = euler_depth[i];
                    }
                    if((euler_depth[i].first==node2)){
                        break;
                    }
                }
            } else if (euler_depth[first_pointer].first==node2){
                for(int i=first_pointer+1; i<euler_depth.size(); i++){
                    if(euler_depth[i].second < min.second){
                        min = euler_depth[i];
                    }
                    if((euler_depth[i].first==node1)){
                        break;
                    }
                }
            }
            return min.first;
        }


        void print_euler_related(){
            for(pair<int,int> u : euler_depth)
                cout << u.first << "," << u.second << "\n";
        }

        //10.2.3-2 거리
        int length(int node1, int node2){
            int lowest_common_ancestor_node = lowest_common_ancestor_by_euler_tour(node1, node2);
            return normal_depth[node1] + normal_depth[node2] - 2* normal_depth[lowest_common_ancestor_node];
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

    Adj_tree ex1_tree(ex1_tree_adj_list, 0);
    
    cout << "<k-th ancestor finding>\n";
    cout << "2nd ancestor of node 6? " << ex1_tree.find_kth_ancestor(7,2) << " (true:1)\n";
    cout << "3th ancestor of node 6? " << ex1_tree.find_kth_ancestor(7,3) << " (true:0)" << endl;
    ex1_tree.print_subtree_of_node(1);
    cout << "expanded-iterative array for eulor tour: (node, depth)\n";
    ex1_tree.print_euler_related();
    cout << "lowest common ancestor of 4,7? " << ex1_tree.lowest_common_ancestor_by_euler_tour(4,7) << " (true:1)" << endl;
    cout << "lowest common ancestor of 4,5? " << ex1_tree.lowest_common_ancestor_by_euler_tour(4,5) << " (true:1)" << endl;
    cout << "lowest common ancestor of 5,3? " << ex1_tree.lowest_common_ancestor_by_euler_tour(5,3) << " (true:0)" << endl;
    cout << "length of 4,7? " << ex1_tree.length(4,7) << " (true:3)" << endl;
    cout << "length of 2,6? " << ex1_tree.length(4,7) << " (true:3)" << endl;


    //example tree 2
    //    0
    // 1 2    3    4
    // 5    6 7 8
    //

}