#include <iostream>
#include <vector>

using namespace std;

//O(n)
vector<int> get_1dimvec_prefix_sum(vector<int> vec){
    vector<int> prefix_vec(vec.size());
    int tempsum = 0;
    for(int i=0; i<vec.size(); i++){
        tempsum += vec[i];
        prefix_vec[i] = tempsum;
    }
    return prefix_vec;
}

//O(mn)
vector<vector<int>> get_2dimvec_prefix_sum(vector<vector<int>> mat){
    int rowsize = mat.size();
    int colsize = mat[0].size();
    
    vector<vector<int>> prefix_mat(rowsize);

    int tempsum = 0;
    vector<int> row_prefix_vec;
    for(int i=0; i<rowsize; i++){
        vector<int> each_col_vec (colsize, 0);
        prefix_mat[i] = each_col_vec;
        tempsum += mat[i][0];
        prefix_mat[i][0] = tempsum;
    }
    tempsum = 0;
    for(int j=0; j<colsize; j++){
        tempsum += mat[0][j];
        prefix_mat[0][j] = tempsum;
    }

    for(int row=1; row<rowsize; row++){
        for(int col=1; col<colsize; col++){
            prefix_mat[row][col] = prefix_mat[row-1][col] + prefix_mat[row][col-1] - prefix_mat[row-1][col-1] + mat[row][col];
        }
    }
    return prefix_mat;
}


//O(1)
int sum_1dimvec_using_prefix_sum_array(int from_idx, int to_idx, vector<int> prefix){
    if(from_idx>0){
        return prefix[to_idx] - prefix[from_idx-1];
    } else if (from_idx==0){
        return prefix[to_idx];
    }
}

//O(1)
int sum_2dimvec_using_prefix_sum_array(int from_row, int from_col, int to_row, int to_col, vector<vector<int>> prefix){
    if(from_row>0 && from_col>0){
        return prefix[to_row][to_col] - prefix[from_row-1][to_col] - prefix[to_row][from_col-1] + prefix[from_row-1][from_col-1];
    }
    else if(from_row == 0){
        if(from_col == 0){
            return prefix[to_row][to_col];
        } else {
            return prefix[to_row][to_col] - prefix[to_row][from_col-1];
        }
    }
    else{
        return prefix[to_row][to_col] - prefix[from_row-1][to_col];
    }
}


int main(){
    vector<int> ex_vector = {1,3,4,8,6,1,4,2};
    vector<int> ex_prefix = get_1dimvec_prefix_sum(ex_vector);
    cout <<"~Ex1~\n" 
    << sum_1dimvec_using_prefix_sum_array(3, 6, ex_prefix) << " (true:19)\n"
    << sum_1dimvec_using_prefix_sum_array(0, 6, ex_prefix) << " (true:27)"
    << endl;

    vector<vector<int>> ex2_vector(4,{0,0,0});
    ex2_vector[0] = {1,1,1}; ex2_vector[1] = {2,2,2}; ex2_vector[2] = {3,3,3}; ex2_vector[3] = {4,4,4};
    vector<vector<int>> ex2_prefix = get_2dimvec_prefix_sum(ex2_vector);
    cout << "\n~Ex2~\n<prefix>\n";
    for(auto u : ex2_prefix){
        for(auto i : u){
            cout << i << " ";
        }
        cout << "\n";
    }
    cout << "<sum query>\n" 
    << sum_2dimvec_using_prefix_sum_array(0,1,2,2,ex2_prefix) <<" (true:12)\n"
    << sum_2dimvec_using_prefix_sum_array(0,0,1,2,ex2_prefix) <<" (true:9)"
    << endl;
}