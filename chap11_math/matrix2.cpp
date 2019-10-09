#include <vector>
#include <iostream>

using namespace std;

class Matrix_GE{ //matrix1.cpp에서 상속해오고 싶지만..
    //for Gaussian elimination
    private:
        vector<vector<double>> mat_val;
        pair<int,int> size;

    public:
        Matrix_GE(){
            mat_val = {{0}};
            size = {1,1};
        }
        
        Matrix_GE(Matrix_GE& other_mat){
            mat_val = other_mat.mat_val;
            size = other_mat.size;
        }

        Matrix_GE(vector<vector<double>> input_vec){
            mat_val = input_vec;
            size = {mat_val.size(), mat_val[0].size()};
        }
    
        void row_swap(int rowidx1, int rowidx2){
            vector<double> temp = mat_val[rowidx1];
            mat_val[rowidx1] = mat_val[rowidx2];
            mat_val[rowidx2] = temp;
        }
        
        void row_multiply_scalar(int rowidx, double scalar){
            for(int i=0; i<size.second; i++){
                mat_val[rowidx][i] *= scalar;
            }
        }

        void row_addto_other_row(int row_from, int row_to, double scalar){
            for(int i=0; i<size.second; i++){
                mat_val[row_to][i] += (scalar * mat_val[row_from][i]);
            }
        }

        void print_matrix(int prec=5){
            for(vector<double> u : mat_val){
                for(double v : u){
                    cout.precision(prec);
                    cout << fixed << v << " ";
                }
                cout << "\n";
            }
        }

        void gaussian_elimination(bool jordan=false){ 
            //나중에할일: 해가 없는 상황이나 해가 무수히 많은 상황에 대한 예외처리
            for(int row_idx=0; row_idx<size.first; row_idx++){
                int try_i=0;
                while(mat_val[row_idx][row_idx]==0){
                    try_i++;
                    row_swap(row_idx, row_idx+try_i);
                }
                row_multiply_scalar(row_idx, (double)1/mat_val[row_idx][row_idx]);
                // print_matrix(); //for debug
                
                int i;
                if(jordan) i=0;
                else i=row_idx;

                for(i; i<size.first; i++){
                    if(i==row_idx) continue;
                    if((double)mat_val[i][row_idx]==0) continue;
                    row_addto_other_row(row_idx, i, (double)-mat_val[i][row_idx]);
                }
            }
        }
};

int main(){
    Matrix_GE ex_lin_eq({{2,4,1,16},{1,2,5,17},{3,1,1,8}});
    // 2x+4y+z=16
    // x+2x+5z=17
    // 3x+y+z=8    -->(true root: 1,3,2)
    ex_lin_eq.row_swap(0,1);
    ex_lin_eq.row_addto_other_row(0,1,-2);
    ex_lin_eq.row_addto_other_row(0,2,-3);
    ex_lin_eq.row_swap(1,2);
    ex_lin_eq.row_multiply_scalar(1,-0.2);
    ex_lin_eq.row_multiply_scalar(2,(double)-1/9);
    ex_lin_eq.print_matrix();

    cout << "****************\n";
    Matrix_GE ex2_lin_eq({{2,4,1,16},{1,2,5,17},{3,1,1,8}});
    ex2_lin_eq.gaussian_elimination();
    ex2_lin_eq.print_matrix(3);
    ex2_lin_eq.gaussian_elimination(true);
    ex2_lin_eq.print_matrix(2);

}