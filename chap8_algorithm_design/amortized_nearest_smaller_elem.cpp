#include <iostream>
#include <vector>
#include <stack>


// 8.2.2
using namespace std;
vector<int> ns_elem(vector<int> vec){
    //return nearlest-smallest element's index for each element of the vector
    //nearlest : in vector position(idx)
    //smallest : in vector value
    //-1 means a minimum position.
    vector<int> result(vec.size(),0);
    stack<int> stk; //vector value stack
    stack<int> idx_stk;

    //initialize
    stk.push(vec[0]);
    idx_stk.push(0);
    result[0] = -1;

    for(int i=1; i<vec.size(); i++){
        if(vec[i] >= stk.top()){ //stack값보다 클 때
            result[i] = idx_stk.top();
            stk.push(vec[i]);
            idx_stk.push(i);
        } else { //작을 떄 : 그보다 큰 값은 스택에서 제거
            while(stk.top() >= vec[i]){
                int verify = stk.top();
                stk.pop(); idx_stk.pop();
            }
            result[i] = idx_stk.top();
            stk.push(vec[i]); idx_stk.push(i);
        }
    }
    return result;
    //개선방안: 두 stack을 만들지 말고 한 스택에 pair를 넣자
}

int main(){
    vector<int> ex_vector = {1,3,4,2,5,3,4,2};
    vector<int> ex_result_vector = ns_elem(ex_vector);
    
    
    cout << "vector value: ";
    for(auto u : ex_vector)
        cout << u << " ";
    cout << endl;
    cout << "index result: ";
    for(auto u : ex_result_vector)
        if(u==-1) cout << "m ";
        else cout << u << " ";
    cout << endl;
    cout << "result value: ";
    for(auto u : ex_result_vector){
        if(u==-1) cout << "m ";
        else cout << ex_vector[u] << " ";
    }
    cout << endl;
}