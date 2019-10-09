#include <vector>
#include <iostream>

using namespace std;

class LCS{
    private:
        string input_x, input_y;
        string longest_common_subsequence;
        int longest_common_subsequence_length;

        int lcs_recursive(int i, int j){ //음좀문제가있음. length는 제대로 나오는데 멤버가 제대로 안나옴
            if(i<0 || j<0) return 0;
            if(input_x[i]==input_y[j]){
                cout << i << j << " \n"; //for debug
                longest_common_subsequence.push_back(input_x[i]); //이렇게 밀어넣으면 안되나봄 (아님 재귀를 잘못돌렸던가)
                return (lcs_recursive(i-1, j-1) + 1);
            } else {
                int candid1 = lcs_recursive(i, j-1);
                int candid2 = lcs_recursive(i-1, j);
                if(candid1-candid2>0){
                    return candid1;
                } else {
                    return candid2;
                }
            }
        }

    public:
        LCS(string x, string y){
            input_x=x;
            input_y=y;
            longest_common_subsequence_length = lcs_recursive(x.size()-1, y.size()-1);

        }

        void print_lcs_result(){
            cout << "length: " << longest_common_subsequence_length << " with members: [";
            for(char c : longest_common_subsequence){
                cout << c << ", ";
            }
            cout << "]\n";
        }
};

int main(){
    string x = "TOUR";
    string y = "OPERA";
    LCS testlcs(x, y);
    testlcs.print_lcs_result();
}