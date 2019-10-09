#include <iostream>
#include <vector>
#include <bitset>

using namespace std;


// 8.1.2. counting subgrid
int factorial(int a){
    int result = 1;
    if(a==0 || a==1) return result;
    for(int i=a; i>1; i--){
        result *= i;
    }
    return result;
}

int combination(int n, int x){
    if(n<x) return 0;
    if(n==x) return 1;
    return factorial(n) / (factorial(x) * factorial(n-x)); //언제나 정수임이 보장되어있음
}

int counting_subgrid(std::vector<bitset<5>> bitvec){ //bitset 크기를 동적으로 받질 못하겠음
    int row_size = 5;
    int count_grid;
    count_grid = 0;
    for(int a=0; a<row_size; a++){
        for(int b = a+1; b<row_size; b++){
            cout << "compare rows: (" << a+1 << "th : " << bitvec[a] << ") with (" << b+1 <<"th : " << bitvec[b];
            int matching_pt_num = (bitvec[a] & bitvec[b]).count();
            int subgrid = combination(matching_pt_num, 2) ;
            if(subgrid>0) count_grid = count_grid + subgrid;
            cout << ") -> #subgrid? : " << subgrid << endl;
        }
    }
    cout << "sum up!! " << count_grid << endl;    
    return count_grid;
}

int main(){
    bitset<5> row1(9);
    bitset<5> row2(12);
    bitset<5> row3(16);
    bitset<5> row4(13);
    bitset<5> row5(0);
    vector<bitset<5>> rowvec = {row1,row2,row3,row4,row5};
    counting_subgrid(rowvec);

}