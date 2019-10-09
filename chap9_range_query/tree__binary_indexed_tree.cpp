#include <iostream>
#include <vector>

using namespace std;

//주의 : index를 1부터 시작하는 것으로 생각하시오....
//(나중에 고치던가,,)
//음..나중에할일2: 코드를정리하시오..클래스로만들던가..


int max_factor_2(int k){
    //책의 p(k)
    return k & -k;
}

//O(nlogn)
vector<int> get_bin_tree(vector<int> vec){
    //0번째에 0 넣어서 밀고 시작하자... (그냥 밑 for문서 k를 하나 빼서 조정해도 된다)
    vector<int>::iterator first_iterator = vec.begin();
    vec.insert(first_iterator, 0);

    vector<int> tree_vec;
    for(int k=1; k<vec.size(); k++){
        int sum_k = 0;
        for(int i = k-max_factor_2(k)+1; i<=k; i++){
            sum_k +=vec[i];
        }
        tree_vec.push_back(sum_k); //여긴 0부터 들어간다...
    }
    return tree_vec;
}

int get_cumul_sum(int to, vector<int> bin_tree){
    //첫자리 index 1로 생각하고 to에 넣을것
    int sum = 0;
    while(to>=1){
        sum += bin_tree[to-1]; //하나 밀고 시작해야해서..
        to -= max_factor_2(to);
    }
    return sum;
}

int get_sum(int from, int to, vector<int> bin_tree){
    //첫자리 index 1로 생각하고 from, to에 넣을것
    return get_cumul_sum(to, bin_tree) - get_cumul_sum(from-1, bin_tree);
}


int main(){
    cout << "<test of max_factor_2>\n";
    for(int k=0; k<10; k++)
        cout << max_factor_2(k);
    cout << "\n";
    //0121412181 (즉, 2진트리의 각 index가 커버할 element 개수를 돌려준다. (맨 앞 0은 버릴것))

    vector<int> ex_vector1 = {1,3,4,8,6,1,4,2};
    vector<int> ex_vector1_binary_tree = get_bin_tree(ex_vector1);
    //     1 3 4 8 6 1 4 2 original_vector
    // [1] o
    // [2] o o
    // [3]     o
    // [4] o o o o
    // [5]         o
    // [6]         o o
    // [7]             o
    // [8] o o o o o o o o
    //bin_tree

    cout << "<ex_vector1>\nvector : ";
    for(int i=0; i<ex_vector1.size(); i++){
        cout << ex_vector1[i] << " ";
    }
    cout << "\nbintree: ";
    for(int i=0; i<ex_vector1.size(); i++){
        cout << ex_vector1_binary_tree[i] << " ";
    }
    cout << " (true: 1 4 4 16 7 8 4 29) \n"
    << "sum of c++idx[0,5]?(our index [1,6]) : " << get_cumul_sum(6, ex_vector1_binary_tree) << " (true:23)\n"
    << "sum of c++idx[2,5]?(out index [3,6]) : " << get_sum(3,6,ex_vector1_binary_tree) <<" (true:19)"
    << endl; //음..idx를 좀..어떻게해야할듯..
}