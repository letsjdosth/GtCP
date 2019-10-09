#include <iostream>

using namespace std;

class Levenshtein_dist{
    private:
        string x, y;
        int dist;

        int cost(int x_idx, int y_idx){
            if(x[x_idx] == y[y_idx]) return 0;
            else return 1;
        }

        int edit_recursive(int x_idx, int y_idx){
            if(x_idx<0 && y_idx<0) return 0;
            if(x_idx<0) return y_idx+1;
            if(y_idx<0) return x_idx+1;

            int candid1 = edit_recursive(x_idx, y_idx-1) + 1;
            int candid2 = edit_recursive(x_idx-1, y_idx) + 1;
            int candid3 = edit_recursive(x_idx-1, y_idx-1) + cost(x_idx, y_idx);
            // cout << "(" << x_idx << "," << y_idx << "):" << candid1 << candid2 << candid3 << endl;
            
            int result = candid1;
            if(candid2<result) result=candid2;
            if(candid3<result) result=candid3;
            return result;
        }

    public:
        Levenshtein_dist(string input_x, string input_y){
            x=input_x;
            y=input_y;
            dist = edit_recursive(x.size()-1, y.size()-1);
        }

        void print_dist(){
            cout << "dist: " << dist << "\n";
        }

        int get_dist(){
            return dist;
        }
};

int main(){
    string x = "LOVE";
    string y = "MOVIE";

    Levenshtein_dist dist(x, y);
    dist.print_dist();
    
}