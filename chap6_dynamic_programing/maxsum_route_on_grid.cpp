#include <iostream>
#include <vector>

using namespace std;

int max_sum_route(int x, int y, vector<vector<int>> grid){
    if (x==0 && y==0) return grid[0][0];
    int n_of_y = grid.size();
    int n_of_x = grid[0].size();
    vector<vector<int>> sum(n_of_y+1, vector<int>(n_of_x+1,0)); 
//맨 위/왼쪽줄도 그냥 같은 loop로 돌려버리기 위해 책과 좀 다르게 만들었음. 
//  grid             -- >   sum
//                          0   0   0   0   0
//  0,0 0,1 ... 0,4         0  1,1(<-grid 0,0까지 가는 최고합 경로의 합 값)
//  1,0                     0
//  2,0                     0      i,j(<-grid i-1,j-1까지 가는 최고합 경로의 합 값)
//  3,0                     0
//  4,0                     0


    for(int y=1; y<=n_of_y; y++){ //<-1부터 시작하는 이유: 첫줄 0으로 비운다
        for(int x=1; x<=n_of_x; x++){
            sum[y][x] = max(sum[y][x-1], sum[y-1][x]) + grid[y-1][x-1];
        }
    }
    return sum[y+1][x+1]; //<-+1을 리턴하는 이유 : sum은 grid와 비교해 해당하는 인덱스가 행열 1씩 밀려있다
}

int main(){
    vector<vector<int>> test_grid(5, vector<int>(5));
    test_grid[0] = {3,7,9,2,7};
    test_grid[1] = {9,8,3,5,5};
    test_grid[2] = {1,7,9,8,5};
    test_grid[3] = {3,8,6,4,10};
    test_grid[4] = {6,3,9,7,8};

    int test_result = max_sum_route(4, 4, test_grid);
    string assert = "F";
    if(test_result == 67) assert = "T";
    cout << "test result : "<< test_result << " (" << assert << ")\n";

}