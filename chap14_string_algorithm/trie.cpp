#include <iostream>
#include <vector>

using namespace std;


class Trie{
    private:
        vector<vector<int>> trie_data;
        vector<char> char_symbol;

        void add_node(){
            vector<int> new_node = {0,0,0,0,0,0,0,0,0,0,
                                    0,0,0,0,0,0,0,0,0,0,
                                    0,0,0,0,0,0,0};
            trie_data.push_back(new_node);
        }

        int char_idx(char input_char){
            int curr = input_char - 'A';
            if (curr>25){
                curr = input_char - 'a';
            }
            return curr;
        }

        void input_1char(char input_char, int this_node){
            //if root node, set last_node_idx=-1
            int input_char_idx = char_idx(input_char);
            int now_node_idx = trie_data.size();
            trie_data[this_node][input_char_idx] = now_node_idx;
            add_node();
            char_symbol.push_back(input_char);
        }

        void mark_end(int this_node){
            trie_data[this_node][26]++;
        }

    public:
        void input_string(string input_str){
            int this_node = 0;
            for(int i=0; i<input_str.size(); i++){
                char c = input_str[i];
                int exist = trie_data[this_node][char_idx(c)];
                if(exist){
                    this_node = trie_data[this_node][char_idx(c)];
                } else {
                    input_1char(c, this_node);
                    this_node = trie_data.size()-1;
                }
            }
            mark_end(this_node);
        }

        Trie(string input_str){
            add_node();
            char_symbol.push_back('0');
            input_string(input_str);
        }

        void print_trie_data(){
            int i=0;
            for(auto u : trie_data){
                cout << "node" << i << " [a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, end, ]\n";
                cout << "(" << char_symbol[i] <<")   [";
                for(int v : u){
                    cout << v << ", ";
                }
                cout << "]\n";
                i++;
            }
        }
};


int main(){
    Trie text_trie("canal");
    text_trie.print_trie_data();
    // text_trie.input_string("aef");
    // text_trie.print_trie_data();
    
    cout << "\n";
    text_trie.input_string("CANDY");
    text_trie.print_trie_data();

    cout << "\n";
    text_trie.input_string("the");
    text_trie.print_trie_data();

    cout << "\n";
    text_trie.input_string("there");
    text_trie.print_trie_data();
}