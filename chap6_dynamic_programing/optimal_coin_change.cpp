#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int solve_coinchange(int x, std::vector<int> coins){
    int INF = std::numeric_limits<int>::max()-1; //1 안빼주면 더하다가 14번째줄에서 2의보수표현에 의해 음수로 넘어간당
    if(x<0) return INF;
    if(x==0) return 0;
    int best = INF;
    for(auto c : coins) {
        best = min(best, solve_coinchange(x-c, coins)+1);
    }
    return best;
}

int using_memoization_solve_coinchange(int x, vector<int> coins, vector<bool>& ready, vector<int>& value){
    int INF = std::numeric_limits<int>::max()-1;
    if(x<0) return INF;
    if(x==0) return 0;
    if (ready[x]) return value[x];
    int best = INF;
    for(auto c : coins) {
        best = min(best, using_memoization_solve_coinchange(x-c, coins, ready, value)+1);
    }
    ready[x] = true;
    value[x] = best;
    return best;
}    

int using_loop_solve_coinchange(int x, vector<int> coins){
    int INF = std::numeric_limits<int>::max()-1;
    vector<int> value(x+1);
    value[0]=0;
    for(int i=1; i<=x; i++){
        value[i] = INF;
        for(auto c : coins){
            if(i-c >=0){
                value[i] = min(value[i], value[i-c]+1);
            }
        }
    }
    return value[x];
}

int print_optimal_comp(int x, vector<int> coins){
    int INF = std::numeric_limits<int>::max()-1;
    vector<int> value(x+1);
    vector<int> first(x+1);
    value[0]=0;
    for(int i=1; i<=x; i++){
        value[i] = INF;
        for(auto c : coins){
            if(i-c >= 0 && value[i-c]+1 < value[i]){
                value[i] = value[i-c]+1;
                first[i] = c;
            }
        }
    } //first vector를 메모이제이션해놓고 x 다르게 받을때 또 쓰도록..언젠가....

    cout << x << " : ";
    while(x>0){
        cout << first[x] << " ";
        x -= first[x];
    }
    cout << "\n";
}

int number_of_comp(int x, vector<int> coins){
    vector<int> count(x+1);
    count[0] = 1; //0이 딱 되는 케이스에 1 더해주기 위함
    for(int i=1; i<=x; i++){
        for(auto c: coins){
            if(i-c >=0) { //i-c<0 인경우는 이 if문에 걸리지 않아서 안 더하고 그냥 넘어가게 된다
                count[i] += count[i-c];
            }
        }
    }
    return count[x];
}


int main(){
    vector<int> coin_vector = {1,3,4};
    vector<int> assert_vector = {0,1,2,1,1,2,2,2,2,3,3};
    int best_result;

    
    for(int i=0; i<=10; i++){
        // basic version
        best_result = solve_coinchange(i, coin_vector); 
        string assert = "F";
        if(best_result==assert_vector[i]) assert = "T";
        cout << "x="<< i <<" : optimal result="<< best_result << " " << assert << endl;
    }

    for(int i=0; i<=10; i++){
        //memoization
        vector<bool> ready(20);
        vector<int> value(20);
        best_result = using_memoization_solve_coinchange(i, coin_vector, ready, value);
        string assert = "F";
        if(best_result==assert_vector[i]) assert = "T";
        cout << "x="<< i <<" : optimal result="<< best_result << " " << assert << endl;
    }
    
    for(int i=0; i<=10; i++){
        //using loop
        best_result = using_loop_solve_coinchange(i, coin_vector); 
        string assert = "F";
        if(best_result==assert_vector[i]) assert = "T";
        cout << "x="<< i <<" : optimal result="<< best_result << " " << assert << endl;
    }

    for(int i=0; i<=10; i++){
        //test print
        print_optimal_comp(i, coin_vector);
    }

    for(int i=0; i<=10; i++){
        //number of composition(solution)
        int num = number_of_comp(i, coin_vector);
        cout << "x=" << i << " : number_of_solution=" << num << endl;
    }
}
