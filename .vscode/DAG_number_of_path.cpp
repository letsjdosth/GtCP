#include <iostream>
#include <vector>

using namespace std;
int num_path(int from, int to, vector<vector<int>> dag, vector<int> topological_sorted){
    int num_nodes = dag.size();
    vector<int> path_vector(num_nodes);
    path_vector[from] = 1;

    int start_point;
    for(int i=0; i<num_nodes; i++){
        if(topological_sorted[i] == from){
            start_point = i;
            break;
        }
    }
    for(int topo_vec_idx=start_point+1; topo_vec_idx<num_nodes; topo_vec_idx++){
        for(int j=0; j<topo_vec_idx; j++){
            bool path_exist_flag = false;
            for (int edgeto : dag[topological_sorted[j]]){
                if (edgeto == topological_sorted[topo_vec_idx]) path_exist_flag=true;
            }
            if(path_exist_flag){
                path_vector[topological_sorted[topo_vec_idx]] += path_vector[topological_sorted[j]]; 
            }
        }
        
    }
    return path_vector[to];
}


int main(){
    //example
    // 0 -> 1 -> 2
    // |    ^  \ |
    // v    |   vv
    // 3 -> 4    5
    vector<vector<int>> ex_dag(6);
    ex_dag[0].push_back(1); ex_dag[0].push_back(3);
    ex_dag[1].push_back(2); ex_dag[1].push_back(5);
    ex_dag[2].push_back(5);
    ex_dag[3].push_back(4);
    ex_dag[4].push_back(1);
    vector<int> ex_dag_topo_sorted = {0,3,4,1,2,5};

    cout << "number of paths : "<< num_path(0, 5, ex_dag, ex_dag_topo_sorted) << " (in fact, 4) \n";
    cout << "number of paths : "<< num_path(0, 2, ex_dag, ex_dag_topo_sorted) << " (in fact, 2) \n";
    cout << "number of paths : "<< num_path(3, 5, ex_dag, ex_dag_topo_sorted) << " (in fact, 2)";
}