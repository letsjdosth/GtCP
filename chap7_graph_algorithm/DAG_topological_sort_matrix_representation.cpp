#include <iostream>
#include <vector>

using namespace std;

vector<int> get_firstnode(vector<vector<int>> dag_mat, vector<bool> processed){
    // 선행 edge 없는 node 찾기
    vector<int> start_node;
    int num_nodes = dag_mat.size();
    
    for(int col_idx=0; col_idx<num_nodes; col_idx++){
        if(processed[col_idx]) continue;
        
        bool col_flag=true;
        for(int row_idx=0; row_idx<num_nodes; row_idx++){
            if(dag_mat[row_idx][col_idx]!=0){
                col_flag=false;
                break;
            }
        }
        if (col_flag =true) start_node.push_back(col_idx);
    }
    return start_node;
}


vector<int> topo_sort_mat(vector<vector<int>> dag){
    int num_nodes = dag.size();
    vector<vector<int>> edge_status;
    edge_status = dag; //copy
    vector<bool> processed_node(num_nodes, false);
    vector<int> result;


    while(1){
        vector<int> stage_start_vec;
        stage_start_vec = get_firstnode(edge_status, processed_node);

        //걍 첫번째꺼 넣자
        if(stage_start_vec.empty()){
            break;
        } else {
            //result에 넣고
            int proc_node = stage_start_vec[0];
            result.push_back(proc_node);
            processed_node[proc_node] = true;
            //그래프에서 제거
            for(int col_idx=0; col_idx<num_nodes; col_idx++){
                edge_status[proc_node][col_idx] = 0;
            }
        }
    }
    return result;
}



int main(){
    //for test
    //      1
    //   /^   \v
    // 0 -> 2 -> 4 
    //   \v   \v/^
    //      3 -> 5

    vector<vector<int>> dag(6, {0,0,0,0,0,0});
    dag[0][1] = 1; dag[0][2] = 1; dag[0][3] =1;
    dag[1][4] = 1; 
    dag[2][4] = 1; dag[2][5] = 1;
    dag[3][4] = 1; dag[3][5] = 1;

    vector<int> result;
    result = topo_sort_mat(dag);

    cout << "answer : 0 1 2 3 4 5\n" <<"result : ";
    for(int i=0; i<6; i++){
        cout << result[i] << " ";
    }
    cout << endl;

}