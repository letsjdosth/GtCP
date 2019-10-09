#include <vector>
#include <iostream>

using namespace std;

class Matrix{
    //주의: 메모리누수가 어디서나고있을지도모른다... (할당연산자 오버라이딩등등 때문에 개판일 것 같음..) 하지만.. 음 모르겠다...
    //할일:
    //  1. 연산들에대해 사이즈체크코드
    //  2. 상속받아서 square matrix / vector에 대해서 연산들 더 정의
    //참고: https://modoocode.com/202 (연산자 오버로딩)
    private:
        vector<vector<double>> mat_val;
        pair<int,int> size;
    
    public:
        Matrix(){
            mat_val = {{0}};
            size = {1,1};
        }
        
        Matrix(Matrix& other_mat){
            mat_val = other_mat.mat_val;
            size = other_mat.size;
        }

        Matrix(vector<vector<double>> input_vec){
            mat_val = input_vec;
            size = {mat_val.size(), mat_val[0].size()};
        }

        Matrix& operator=(const Matrix& rhs) { //할당연산은 &를 리턴해야하나봄. 근데 왜 arg rhs에서 const를 떼면 컴파일러가 뱉을까...?
            if(this==&rhs) return *this;
            else {
                mat_val = rhs.mat_val;
                size = rhs.size;
                return *this;
            }
        }

        vector<double> operator[](int idx) { //[] 접근 오버로딩
            return mat_val[idx];
        }
        
        Matrix& operator+=(Matrix& rhs){ //할당연산은 &리턴
            for(int i=0;i<size.first;i++){
                for(int j=0;j<size.second;j++){
                    mat_val[i][j] += rhs[i][j];
                }
            }
            return *this;
        }

        Matrix operator+(Matrix& rhs) const{
            Matrix result(this->mat_val);
            result += rhs;
            return result;
        }

        Matrix& operator*=(Matrix& rhs){
            //나중에 사이즈체크코드 넣고 안맞으면 에러낼것
            vector<vector<double>> result_mat_val;
            pair<int,int> result_size = {this->size.first, rhs.size.second};
            for(int i=0; i<result_size.first; i++){
                vector<double> new_row(result_size.second, 0);
                result_mat_val.push_back(new_row);
                for(int j=0; j<result_size.second; j++){
                    double element_sum=0;
                    for(int k=0; k<(this->size.second);k++){
                        element_sum += (this->mat_val[i][k] * rhs.mat_val[k][j]);
                    }
                    result_mat_val[i][j] = element_sum;
                }
            }
            mat_val=result_mat_val;
            size = result_size;
            return *this;
        }

        Matrix& operator*=(double scalar){
            for(int i=0; i<size.first; i++){
                for(int j=0; j<size.second; j++){
                    mat_val[i][j] *= scalar;
                }
            }
            return *this;
        }

        Matrix operator*(Matrix& rhs) const{
            Matrix result(this->mat_val);
            result *= rhs;
            return result;
        }

        
        Matrix operator*(double rhs) const{
            Matrix result(this->mat_val);
            result *= rhs;
            return result;
        }

        void transpose(){
            vector<vector<double>> new_mat_val;
            for(int i=0; i<size.second; i++){
                vector<double> new_row(size.first);
                new_mat_val.push_back(new_row);
                for(int j=0; j<size.first; j++){
                    new_mat_val[i][j] = mat_val[j][i];
                }
            }
            mat_val = new_mat_val;
            size.swap(size);
        }

        void print_matrix(){
            for(auto u : mat_val){
                for(auto v : u){
                    cout << v << " ";
                }
                cout << "\n";
            }
        }

        Matrix pow(int n){
            Matrix result(mat_val);
            if(n==1) return result;
            else if(n%2==1){
                result = (result.pow(n-1) * result);
                return result;
            } else {
                result = result.pow(n/2);
                result = result*result;
                return result;
            }
        }
};


int main(){
    //matrix operator[] overloading test
    Matrix ex_mat({{1,2},{3,4}});
    cout << ex_mat[1][0] << " (true:3)" << endl;
    
    //matrix transpose test
    ex_mat.transpose();
    cout << ex_mat[1][0] << " (true:2)" << endl;

    Matrix ex2_mat({{6,13,7,4},{7,0,8,2},{9,5,4,18}});
    cout << ex2_mat[0][2] << " (true:7)" << endl;
    ex2_mat.transpose();
    cout << ex2_mat[2][0] << " (true:7)" << endl;


    //matrix operator += overloading test
    Matrix ex2_mat_for_add({{0,0,0},{0,0,0},{1,1,1},{0,0,0}});
    ex2_mat+=ex2_mat_for_add;
    cout << ex2_mat[2][0] << " (true:8)" << endl;

    //matrix operator + overloading test
    ex2_mat = ex2_mat + ex2_mat_for_add;
    cout << ex2_mat[2][0] << " (true:9)" << endl;


    //Matrix operation *= overloading test (with matrix)
    Matrix ex3_mat({{1,4},{3,9},{8,6}});
    Matrix ex3_mat_for_multiply({{1,6},{2,9}});
    ex3_mat *= ex3_mat_for_multiply;
    cout << ex3_mat[0][1] << " (true:42)" << endl;
    cout << ex3_mat[1][1] << " (true:99)" << endl;
    
    //Matrix operation * overloading test (with matrix)
    Matrix ex3_mat_for_multiply_result;
    ex3_mat_for_multiply_result = ex3_mat * ex3_mat_for_multiply;
    cout << ex3_mat_for_multiply_result[0][1] << " (true:432)" << endl;
    cout << ex3_mat_for_multiply_result[1][1] << " (true:1017)" << endl;
    
    //Matrix operation *= and * overloading test (with scalar)
    Matrix ex4_mat({{1,4},{3,9},{8,6}});
    ex4_mat*=2;
    ex4_mat.print_matrix();

    Matrix ex4_mat_for_multiply_result;
    ex4_mat_for_multiply_result = ex4_mat * 0.3;
    ex4_mat_for_multiply_result.print_matrix();

    //matrix pow test
    Matrix ex5_mat({{2,0},{0,3}});
    ex5_mat = ex5_mat.pow(3);
    ex5_mat.print_matrix();

    
    //example of linear recurrence : Fibonacci numbers
    cout << "<Fibonacci numbers>\n";
    Matrix leftX({{0,1},{1,1}});
    Matrix start({{1},{1}});
    Matrix fibo5_6; //여기에 바로 = 써서 집어넣고싶은데 에러남 뭘 오버라이딩해야할지 모르겠음
    fibo5_6 = leftX.pow(5)*start;
    fibo5_6.print_matrix();

}