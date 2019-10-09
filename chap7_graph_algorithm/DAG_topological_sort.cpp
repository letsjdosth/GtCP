#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<int> topological_sort(vector<vector<int>> dag){
    //권장: dag의 node number를 왠만하면 뒤쪽 노드가 커지도록 넣고 시작할 것
    //(좀 순환논리지만 음 멍청해서 어쩔수가없네요)

    //edge status initialize
    // 안가본edge면 1, 가본edge면 0
    vector<vector<int>> edge_status = dag; 
    for(vector<int> node : dag){
        for(int i=0; i<node.size(); i++){
            node[i] = 1;
        }
    }

    //node status initialize
    // 0: not processed.  1: visited  2: all edges starting from this node are processed
    int num_nodes = dag.size();
    vector<int> node_status(num_nodes, 0); 
    

    vector<int> result;
    bool loop_flag = true;
    while(loop_flag){
        //한 stage의 시작노드 정하기
        int proc_node = -1;
        for(int node_idx=0; node_idx<num_nodes; node_idx++){
            if(node_status[node_idx]==0 || node_status[node_idx]==1) {
                proc_node=node_idx;
                break;
            }
        }
        // cout << "choson starting node:" << proc_node << endl; //for debug
        if(proc_node == -1) {
            //모든 노드가 2란 소리이므로 모두 처리되었다.
            loop_flag=0;
            break;
        }
        
        //at proc_node
        bool inner_loop_flag = true;
        vector<int> stage_result;
        while(inner_loop_flag){ //경로 진행
            // cout << "now node: " << proc_node <<"\n"; //for debug
            // stage_result.push_back(proc_node); <- 어차피 edge상태가 바뀌어서 굳이 경로를 저장할필요 없는듯 하지만
            //생각: node 번호가 역순이 뒤가 아닐경우, 밑에 나이브한 포문대신
            //stage 경로를 저장한 후, 이를 역으로 따라가야하는 경우를 구현해야할수도있을것같음
            node_status[proc_node]=1;
            
            int next_proc_node = -1;
            for(int edge_idx=0; edge_idx<dag[proc_node].size(); edge_idx++){ 
                //노드가활성화되어있고 해당노드를따라갔을때 그 노드의 status가 2(처리끝남)이 아니라면 for문 진행
                if(edge_status[proc_node][edge_idx] && node_status[dag[proc_node][edge_idx]]!=2){ 
                    //2가아니라면 이란 조건을 여기서 달 필요 엇ㅂ도록 좀있다가 이어지는 node가 2면 다 edge를 비활성화시키는
                    //단계를 추가하자 (여기도 좀있다고치자)
                    next_proc_node = dag[proc_node][edge_idx];
                    // cout << "next node: " << next_proc_node << endl; //for debug
                    edge_status[proc_node][edge_idx]=0;
                    break;
                }
            }

        
            
            // cout << "node" << proc_node << " status: " << node_status[proc_node] << endl; //for debug
            if (next_proc_node == -1){
                //다음 node에서 모든 edge가 비활성화되었으면, 이번 스테이지 끝내자
                inner_loop_flag =false;
                result.push_back(proc_node);
                node_status[proc_node]=2;
            }
            proc_node = next_proc_node;
        }
      
        //stage 정리
        //기존 0/1이었던 모든 노드 돌며 그 노드부터 시작하는 edge가 비활성화되었는지 확인
        //만약 다 비활성화되었다면 2로 바꾸고 결과에 넣자
        
        
        for (int node_idx=num_nodes-1; node_idx>=0; node_idx--){ 
            //<-나이브하게 nodenum의 역순으로 도는데 음..좀 문제있는듯.
            //정말 그래프의 뒤부터 돌아야함. 하지만 노드번호가 엉망으로 되어있으면
            //그래프의 앞부터 체크하게 되고, 그럼 2로 바꿀 뒤에있는 노드를 놓침
            bool edge_live_flag = false; //하나라도 살아있으면 1
            if((node_status[node_idx]==0) || (node_status[node_idx]==1)){
                for(int edge_idx=0; edge_idx<dag[node_idx].size(); edge_idx++){
                    if(node_status[(dag[node_idx][edge_idx])]!=2) //다음노드가 2가아니면
                        edge_live_flag =true;
                }
                if(edge_live_flag==false) { //다음연결노드들이 다 node status 2면 2로바꾸고 결과에넣자
                    node_status[node_idx]=2;
                    result.push_back(node_idx);
                }
            }
        }
        loop_flag=false;
        for (int node_idx=num_nodes-1; node_idx>=0; node_idx--){
            if(node_status[node_idx] != 2){
                loop_flag=true;
                break;
            }
        }
    }

    //stage_result 뒤집자
    vector<int> final;
    for(int i=result.size()-1; i>=0; i--){
        final.push_back(result[i]);
    }
    // cout << "\n";
    return final;

}

int main(){
    // DAG : directed acyclic graph
    // no cycle, directed graph

    //example
    // 0 -> 1 -> 2 ->5
    // ^    ^   ^
    // |    |  /  
    // 3 -> 4
    vector<vector<int>> ex_dag(6);
    ex_dag[0].push_back(1);
    ex_dag[1].push_back(2);
    ex_dag[2].push_back(5);
    ex_dag[3].push_back(0); ex_dag[3].push_back(4);
    ex_dag[4].push_back(1); ex_dag[4].push_back(2);
    vector<int> sorted_result = topological_sort(ex_dag);
    cout << "result of topological sort. \n answer: 3 0 4 1 2 5 \n (or)  : 3 4 0 1 2 5\n result:";
    for(int elem : sorted_result){
        cout << " " << elem;
    } 
    cout << "\n";

    //example2
    // 0 -> 1 -> 2
    // |    ^  \ |
    // v    |   vv
    // 3 -> 4    5
    vector<vector<int>> ex_dag2(6);
    ex_dag2[0].push_back(1); ex_dag2[0].push_back(3);
    ex_dag2[1].push_back(2); ex_dag2[1].push_back(5);
    ex_dag2[2].push_back(5);
    ex_dag2[3].push_back(4);
    ex_dag2[4].push_back(1);
    vector<int> sorted_result2 = topological_sort(ex_dag2);
    cout << "result of topological sort. \n answer: 0 3 4 1 2 5 \n result:";
    for(int elem : sorted_result2){
        cout << " " << elem;
    } 
    cout << "\n";
    //ex2를 보면 아직 문제가 있음을 확인할 수 있음
    //1. 5가 2가 되는 순간, 5로 오는 모든 edge가 다 비활성화되고, 그래서 node 1의 status가 2가 되어야 함
    //마지막 노드가 2가 될 때, 역순으로 거슬러올라가며 체크해야 할 듯 
    // (<마지막 노드로 오는 edge 모두 비활성화 후, 모든노드 비활성화된 node status 2로 변경 <을 거슬러올라가며)
    //2. 정답은 0 3 4 1 2 5 임...
}
