#include <iostream>
#include <vector>

using namespace std;

class Z_class{
    private:
        string save_str;
        vector<int> z_array;
        int pointer_x, pointer_y;

        void fill_z_array(){
            for(int k=1; k<save_str.size(); k++){
                if(pointer_y<k){
                    int z_val = 0;
                    int iter = 0;
                    while(iter<(save_str.size()-k)){
                        if(save_str[k+iter]==save_str[iter])
                            z_val++;
                        else
                            break;
                        iter++;
                    }
                    z_array[k] = z_val;
                    pointer_x = k;
                    pointer_y = k + z_val - 1;
                } else if(pointer_y>=k && k+z_array[k-pointer_x]<=pointer_y){
                    z_array[k] = z_array[k-pointer_x];
                } else {
                    int z_val = pointer_y - k + 1;
                    int iter = 0;
                    while(pointer_y+1+iter < save_str.size()-1){
                        if(save_str[pointer_y-k+1+iter]==save_str[pointer_y+1+iter]){
                            z_val++;
                        } else {
                            break;
                        }
                        iter++;
                    }
                    z_array[k] = z_val;
                }
            }
        }

    public:
        Z_class(string input_str){
            save_str = input_str;
            z_array.resize(save_str.size());
            z_array[0]=-1;
            pointer_x=-1;
            pointer_y=-1;

            fill_z_array();
        }
        
        void print_z_array(){
            cout << "[";
            for(auto u : z_array){
                cout << u << ", ";
            }
            cout << "] with x=" << pointer_x << " and y=" << pointer_y << "\n";
        }

        vector<int> get_z_array(){
            return z_array;
        }

};

int main(){
    string test_str = "ABCABCABAB";
    Z_class test_Z(test_str);
    test_Z.print_z_array();
}