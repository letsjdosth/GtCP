#include <iostream>
#include <vector>

using namespace std;

class Polynomial_hash{
    private:
        string input_str;
        int str_size; 
        vector<int> hash_vector;
        vector<int> powerA_vector;
        const int A = 3;
        const int mod = 97;

        void make_hash_vector(){
            hash_vector[0]= (int)input_str[0];
            for(int i=1; i<str_size; i++){
                hash_vector[i] = (hash_vector[i-1]*A + ((int)input_str[i])) % mod;
            }
        }
        void make_powerA_vector(){
            powerA_vector[0]=1;
            for(int i=1; i<str_size; i++){
                powerA_vector[i] = (powerA_vector[i-1]*A) % mod;
            }
        }


    public:
        Polynomial_hash(string input){
            input_str = input;
            str_size = input_str.size();
            hash_vector.resize(str_size);
            powerA_vector.resize(str_size);

            make_hash_vector();
            make_powerA_vector();
        }

        //O(1)
        int get_substring_polynomial_hash(int start_idx, int end_idx){
            int hash_val;
            if(start_idx==0) hash_val = hash_vector[end_idx];
            else{
                hash_val = (hash_vector[end_idx] - hash_vector[start_idx-1]*powerA_vector[end_idx-start_idx+1]) % mod;
            }
            if(hash_val<0) hash_val += mod;
            return hash_val;
        }

        int get_polynomial_hash(){
            return get_substring_polynomial_hash(0, str_size-1);
        }

        void print_for_debug(){
            for(auto u : powerA_vector){
                cout << u << " ";
            }
            cout << "\n";
            for(auto u : hash_vector){
                cout << u << " ";
            }
            cout << "\n";
        }
    
};

int main(){
    Polynomial_hash test("hellowww");
    test.print_for_debug();
    cout << "hash of hellowww: " << test.get_polynomial_hash() << endl;
    cout << "hash of hellow: " << test.get_substring_polynomial_hash(0,5) << endl;
    cout << "hash of llo: " << test.get_substring_polynomial_hash(2,4) << endl;
}