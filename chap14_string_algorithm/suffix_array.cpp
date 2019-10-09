#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Suffix{
    private:
        string save_str;
        vector<int> num_array;
        vector<tuple<int,int,int>> temp_array;
        vector<int> suffix_array;
    
        void first_stage(){
            for(int i=0; i<save_str.size(); i++){
                num_array[i] = (int)save_str[i] - 64;
            }
        }

        void iter_stage(int window_size){
            for(int i=0; i<save_str.size(); i++){
                int first = num_array[i];
                int second;
                if(i+window_size<save_str.size())
                    second = num_array[i+window_size];
                else
                    second=0;
                int third = i;
                temp_array[i] = make_tuple(first, second, third);
            }
        }

        void tuple_sort(){
            stable_sort(temp_array.begin(), temp_array.end());
        }

        void update_num_array(){
            int rank = 0;
            tuple<int, int, int> last = make_tuple(-1,-1,-1);
            for(int i=0; i<save_str.size(); i++){
                int temp_1, temp_2, idx;
                int last_1, last_2, __;
                tie(temp_1, temp_2, idx) = temp_array[i];
                tie(last_1, last_2, __) = last;
                if(temp_1==last_1 && temp_2==last_2){
                    num_array[idx] = rank;
                } else {
                    rank++;
                    num_array[idx] = rank;
                }
                last = temp_array[i];
            }
        }

        void print_detail(bool temp, bool suffix){
            if(temp){
                cout << "temp_array: [";
                for(tuple<int,int,int> u : temp_array){
                    int first, second, third;
                    tie(first,second,third) = u;
                    cout << "<" << first << "," << second << "," << third << ">,";
                }
                cout << "]\n";
            }
            if(suffix){
                cout << "num_array: [";
                for(int u : num_array){
                    cout << u << ",";
                }
                cout << "]\n";
            }
        }

        void make_suffix_array(){
            for(int i=0; i<save_str.size(); i++){
                suffix_array[num_array[i]-1]=i;
            }
        }

        void stage_excute(){
            int iter = 1;
            int window = 1 << iter-1;
            while(window <= save_str.size()*2){
                cout << "iter_stage: " << iter << "\n";
                iter_stage(window);
                cout << "before sort (check temp vec!)\n";
                print_detail(true, false);
                tuple_sort();
                update_num_array();
                cout << "after sort (check sort result and updated suffix!)\n";
                print_detail(true, true);
                iter++;
                window = 1 << iter-1;
            }
        }

    public:
        Suffix(string input_str){
            save_str = input_str;
            num_array.resize(save_str.size());
            temp_array.resize(save_str.size());
            suffix_array.resize(save_str.size());
        }

        void run(){
            first_stage();
            stage_excute();
            make_suffix_array();
        }

        void print_num_array(){
            print_detail(false, true);
        }

        void print_suffix_array(){
            cout << "suffix_array: [";
            for(int u : suffix_array){
                cout << u << ",";
            }
            cout << "]\n";
        }

        vector<int> get_num_array(){
            return num_array;
        }

        vector<int> get_suffix_array(){
            return suffix_array;
        }

};

int main(){
    string test_str = "ABAACBAB";
    Suffix test_suffix(test_str);
    test_suffix.run();
    test_suffix.print_suffix_array();

}