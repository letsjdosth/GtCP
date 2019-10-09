#include <iostream>
#include <vector>

using namespace std;

int succ(int x, int k=1){
    //successor graph 
    // 9 -> 3 <- 1         6 -> 2 -> 5
    //      |    ^        ^^      <- 
    //      v /-/        /  \ 
    //      7           4    8
    
    //x>=9 면 error 발생시키자
    vector<int> successor = {0,3,5,7,6,2,2,1,6,3}; //0번쨰는 더미
    // if(x+k >= successor.size()) x = (x+k)%successor.size();
    if(k==1) return successor[x];
    if(k>1) return succ(successor[x], k-1); 
}


int effective_succ(int x, int k=1){
    //x>=9 면 error 발생시키자
    vector<int> successor = {0,3,5,7,6,2,2,1,6,3}; //0번쨰는 더미
    // if(x+k >= successor.size()) x = (x+k)%successor.size();
    if(k==1) return successor[x];
    if(k>1 && k%2==0) return succ(succ(x,k/2), k/2);
    else if(k>1) return succ(successor[x], k-1);  
}

//이 함수는 succ의 successor graph에 의존
//bool value: just set wethear represent each string of start node or cycle length or not
//return is always cycle length
int floyd_cycle(int start, bool cycle_start_node=true, bool cycle_length=true){
    int a = succ(start);
    int b = succ(start,2);
    while(a != b){
        a = succ(a);
        b = succ(b,2);
    } // a는 k번, b는 2k번 이동
    a = start;
    while(a != b){
        a = succ(a);
        b = succ(b);
    }
    int cycle_first_node = a;
    if (cycle_start_node) cout<< "cycle start node: " << cycle_first_node << endl;

    b=succ(a);
    int length=1;
    while(a != b){
        b = succ(b);
        length++;
    }
    if (cycle_length) cout<< "cycle length: " << length << endl;
    return length;
}

int main(){
    //succ test
    cout << "succ: "<< succ(4) << " effective_succ: "<< effective_succ(4) << " true: 6" << endl;
    cout << "succ: "<< succ(4,6) << " effective_succ: "<< effective_succ(4,6) << " true: 2" << endl;
    cout << "succ: "<< succ(4,11) << " effective_succ: "<< effective_succ(4,11) << " true: 5" << endl;

    floyd_cycle(1);
    floyd_cycle(4);
}